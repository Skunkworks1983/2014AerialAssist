package com.pi.robot.mesh;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;

import com.pi.math.TransMatrix;
import com.pi.math.Vector3D;
import com.pi.robot.robot.RobotStateManager;

public class Mesh {
	private List<MeshVertex> verticies;
	private List<Integer> indicies;
	private int polygonSize;

	public FloatBufferColor defaultColor;

	private IntBuffer indexBuffer;
	private FloatBuffer vertexBuffer;
	private FloatBuffer normalBuffer;
	private FloatBuffer colorBuffer;
	private IntBuffer bufferObjects;

	public Mesh(List<MeshVertex> verts, List<Integer> indz, int polygonSize) {
		this.verticies = verts;
		this.indicies = indz;
		this.polygonSize = polygonSize;
	}

	public void generateBuffers() {
		if (indicies != null) {
			// Gen buffers
			indexBuffer = BufferUtils.createIntBuffer(indicies.size());
			vertexBuffer = BufferUtils.createFloatBuffer(verticies.size() * 3);
			normalBuffer = BufferUtils.createFloatBuffer(verticies.size() * 3);
			for (MeshVertex v : verticies) {
				if (v.color != null) {
					colorBuffer = BufferUtils.createFloatBuffer(verticies
							.size() * 4);
					break;
				}
			}
			for (int i = 0; i < verticies.size(); i++) {
				MeshVertex mV = verticies.get(i);
				vertexBuffer.put(mV.getPosition().x);
				vertexBuffer.put(mV.getPosition().y);
				vertexBuffer.put(mV.getPosition().z);

				normalBuffer.put(mV.getNormal().x);
				normalBuffer.put(mV.getNormal().y);
				normalBuffer.put(mV.getNormal().z);

				if (colorBuffer != null) {
					if (mV.color != null) {
						colorBuffer.put(mV.color.getBuffer());
					} else if (defaultColor != null) {
						colorBuffer.put(defaultColor.getBuffer());
					} else {
						colorBuffer.put(RobotStateManager.defaultColor
								.getBuffer());
					}
				}
			}
			vertexBuffer = (FloatBuffer) vertexBuffer.flip();
			normalBuffer = (FloatBuffer) normalBuffer.flip();
			if (colorBuffer != null) {
				colorBuffer = (FloatBuffer) colorBuffer.flip();
			}

			for (int i = 0; i < indicies.size(); i++) {
				indexBuffer.put(indicies.get(i).intValue());
			}
			indexBuffer = (IntBuffer) indexBuffer.flip();
		}
	}

	public void loadToGPU() {
		unloadFromGPU();

		bufferObjects = BufferUtils
				.createIntBuffer(colorBuffer != null ? 4 : 3);

		GL15.glGenBuffers(bufferObjects);
		int vHandle = bufferObjects.get(0);
		int nHandle = bufferObjects.get(1);
		int iHandle = bufferObjects.get(2);
		GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vHandle);
		GL15.glBufferData(GL15.GL_ARRAY_BUFFER, vertexBuffer,
				GL15.GL_STATIC_DRAW);

		GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, nHandle);
		GL15.glBufferData(GL15.GL_ARRAY_BUFFER, normalBuffer,
				GL15.GL_STATIC_DRAW);

		GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, iHandle);
		GL15.glBufferData(GL15.GL_ARRAY_BUFFER, indexBuffer,
				GL15.GL_STATIC_DRAW);
		if (colorBuffer != null) {
			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, bufferObjects.get(3));
			GL15.glBufferData(GL15.GL_ARRAY_BUFFER, colorBuffer,
					GL15.GL_STATIC_DRAW);
		}
	}

	public void unloadFromGPU() {
		if (bufferObjects != null) {
			GL15.glDeleteBuffers(bufferObjects);
			bufferObjects = null;
		}
	}

	public void saveCache(File f) throws IOException {
		DataOutputStream dOut = new DataOutputStream(new BufferedOutputStream(
				new FileOutputStream(f)));
		dOut.writeBoolean(indexBuffer != null);
		dOut.writeInt(polygonSize);
		dOut.writeInt(verticies.size());

		dOut.writeBoolean(defaultColor != null);
		if (defaultColor != null) {
			FloatBuffer buffer = defaultColor.getBuffer();
			dOut.writeByte((byte) (buffer.get() * 255));
			dOut.writeByte((byte) (buffer.get() * 255));
			dOut.writeByte((byte) (buffer.get() * 255));
			dOut.writeByte((byte) (buffer.get() * 255));
		}

		int perc = 0;
		for (int i = 0; i < verticies.size(); i++) {
			int pp = (int) (100 * i / (float) verticies.size());
			if (pp > perc) {
				System.out.print("\r" + pp);
				perc = pp;
			}
			MeshVertex mV = verticies.get(i);
			dOut.writeFloat(mV.getPosition().x);
			dOut.writeFloat(mV.getPosition().y);
			dOut.writeFloat(mV.getPosition().z);

			dOut.writeFloat(mV.getNormal().x);
			dOut.writeFloat(mV.getNormal().y);
			dOut.writeFloat(mV.getNormal().z);

			dOut.writeBoolean(mV.getColor() != null);
			if (mV.getColor() != null) {
				FloatBuffer buffer = mV.getColor().getBuffer();
				dOut.writeByte((byte) (buffer.get() * 255));
				dOut.writeByte((byte) (buffer.get() * 255));
				dOut.writeByte((byte) (buffer.get() * 255));
				dOut.writeByte((byte) (buffer.get() * 255));
			}
		}
		if (indicies == null) {
			dOut.writeInt(0);
		} else {
			dOut.writeInt(indicies.size());
			for (int i = 0; i < indicies.size(); i++) {
				dOut.writeInt(indicies.get(i).intValue());
			}
		}
		dOut.close();
	}

	public static Mesh loadCache(File f) throws IOException {
		DataInputStream dIn = new DataInputStream(new BufferedInputStream(
				new FileInputStream(f)));
		boolean indexed = dIn.readBoolean();
		int polySize = dIn.readInt();
		int vSize = dIn.readInt();
		FloatBufferColor defaultColor = null;

		if (dIn.readBoolean()) {
			defaultColor = new FloatBufferColor();
			defaultColor.set((dIn.readByte() & 0xFF) / 255f,
					(dIn.readByte() & 0xFF) / 255f,
					(dIn.readByte() & 0xFF) / 255f,
					(dIn.readByte() & 0xFF) / 255f);
		}
		List<MeshVertex> verticies = new ArrayList<MeshVertex>(vSize);
		int perc = 0;
		for (int i = 0; i < vSize; i++) {
			int pp = (int) (100 * i / (float) vSize);
			if (pp > perc) {
				// TODO System.out.print("\r" + pp);
				perc = pp;
			}
			Vector3D pos = new Vector3D(dIn.readFloat(), dIn.readFloat(),
					dIn.readFloat());
			Vector3D norm = new Vector3D(dIn.readFloat(), dIn.readFloat(),
					dIn.readFloat());
			norm.normalize();
			verticies.add(new MeshVertex(pos, norm, new float[] { 0, 0 }));
			if (dIn.readBoolean()) {
				FloatBufferColor color = new FloatBufferColor();
				color.set((dIn.readByte() & 0xFF) / 255f,
						(dIn.readByte() & 0xFF) / 255f,
						(dIn.readByte() & 0xFF) / 255f,
						(dIn.readByte() & 0xFF) / 255f);
				verticies.get(verticies.size() - 1).color = color;
			}
		}
		int iSize = dIn.readInt();
		List<Integer> indicies;
		if (iSize == 0) {
			indicies = null;
		} else {
			indicies = new ArrayList<Integer>(iSize);
			for (int i = 0; i < iSize; i++) {
				indicies.add(Integer.valueOf(dIn.readInt()));
			}
		}
		dIn.close();
		Mesh m = new Mesh(verticies, indicies, polySize);
		if (indexed) {
			m.generateBuffers();
		}
		m.defaultColor = defaultColor;
		return m;
	}

	public void add(Mesh m) {
		if (m.polygonSize != polygonSize) {
			throw new RuntimeException("BAD POLYGON SIZE");
		}
		verticies.addAll(m.verticies);
	}

	public List<MeshVertex> getVerticies() {
		return verticies;
	}

	public List<Integer> getIndicies() {
		return indicies;
	}

	public int getPolygonSize() {
		return polygonSize;
	}

	public void apply(TransMatrix m) {
		TransMatrix normalz = new TransMatrix(m).setTranslation(0, 0, 0);
		for (MeshVertex v : verticies) {
			v.position = m.multiply(v.getPosition());
			v.normal = normalz.multiply(v.getNormal());
		}
	}

	public void draw() {
		if (bufferObjects != null) {
			int vHandle = bufferObjects.get(0);
			int nHandle = bufferObjects.get(1);
			int iHandle = bufferObjects.get(2);

			GL11.glEnableClientState(GL11.GL_VERTEX_ARRAY);
			GL11.glEnableClientState(GL11.GL_NORMAL_ARRAY);

			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vHandle);
			GL11.glVertexPointer(3, GL11.GL_FLOAT, 0, 0);

			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, nHandle);
			GL11.glNormalPointer(GL11.GL_FLOAT, 0, 0);

			if (colorBuffer != null) {
				GL11.glEnableClientState(GL11.GL_COLOR_ARRAY);
				GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, bufferObjects.get(3));
				GL11.glColorPointer(4, GL11.GL_FLOAT, 0, 0);
			}

			GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, iHandle);
			GL11.glDrawElements(GL11.GL_TRIANGLES, indexBuffer.limit(),
					GL11.GL_UNSIGNED_INT, 0);

			if (colorBuffer != null) {
				GL11.glDisableClientState(GL11.GL_COLOR_ARRAY);
			}
			GL11.glDisableClientState(GL11.GL_VERTEX_ARRAY);
			GL11.glDisableClientState(GL11.GL_NORMAL_ARRAY);
		} else if (indexBuffer != null) { // TODO Colors
			GL11.glEnableClientState(GL11.GL_VERTEX_ARRAY);
			GL11.glEnableClientState(GL11.GL_NORMAL_ARRAY);
			GL11.glVertexPointer(3, 0, vertexBuffer);
			GL11.glNormalPointer(0, normalBuffer);
			if (colorBuffer != null) {
				GL11.glEnableClientState(GL11.GL_COLOR_ARRAY);
				GL11.glColorPointer(4, 0, colorBuffer);
			}
			GL11.glDrawElements(GL11.GL_TRIANGLES, indexBuffer);
			if (colorBuffer != null) {
				GL11.glDisableClientState(GL11.GL_COLOR_ARRAY);
			}
			GL11.glDisableClientState(GL11.GL_VERTEX_ARRAY);
			GL11.glDisableClientState(GL11.GL_NORMAL_ARRAY);
		} else { // TODO Colors
			GL11.glBegin(getGLType());
			if (getIndicies() != null) {
				for (int i : getIndicies()) {
					GL11.glTexCoord2f(getVerticies().get(i).getTextureUV()[0],
							getVerticies().get(i).getTextureUV()[1]);
					GL11.glNormal3f(getVerticies().get(i).getNormal().x,
							getVerticies().get(i).getNormal().y, getVerticies()
									.get(i).getNormal().z);
					GL11.glVertex3f(verticies.get(i).getPosition().x, verticies
							.get(i).getPosition().y, verticies.get(i)
							.getPosition().z);
				}
			} else {
				for (MeshVertex v : verticies) {
					GL11.glTexCoord2f(v.getTextureUV()[0], v.getTextureUV()[1]);
					GL11.glNormal3f(v.getNormal().x, v.getNormal().y,
							v.getNormal().z);
					GL11.glVertex3f(v.getPosition().x, v.getPosition().y,
							v.getPosition().z);
				}
			}
			GL11.glEnd();
		}
	}

	public int getGLType() {
		switch (polygonSize) {
		case 1:
			return GL11.GL_POINTS;
		case 2:
			return GL11.GL_LINES;
		case 3:
			return GL11.GL_TRIANGLES;
		case 4:
			return GL11.GL_QUADS;
		default:
			return GL11.GL_POLYGON;
		}
	}
}
