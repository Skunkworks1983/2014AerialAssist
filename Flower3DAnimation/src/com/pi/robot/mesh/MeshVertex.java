package com.pi.robot.mesh;

import com.pi.math.Vector3D;

public class MeshVertex {
	Vector3D position;
	Vector3D normal;
	FloatBufferColor color;
	private float[] textureUV;

	public MeshVertex(Vector3D pos, Vector3D normal, float[] tex) {
		this.position = pos;
		this.normal = normal;
		this.textureUV = tex;
	}
	
	public void setColor(FloatBufferColor color) {
		this.color = color;
	}
	
	public FloatBufferColor getColor() {
		return color;
	}

	public Vector3D getPosition() {
		return position;
	}

	public Vector3D getNormal() {
		return normal;
	}

	public float[] getTextureUV() {
		return textureUV;
	}

	public int hashCode() {
		return position.hashCode();
	}

	public boolean equals(Object o) {
		if (o instanceof MeshVertex) {
			return ((MeshVertex) o).getPosition().equals(getPosition());
		}
		return false;
	}
}
