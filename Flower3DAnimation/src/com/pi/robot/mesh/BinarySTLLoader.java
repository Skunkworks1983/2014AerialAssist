package com.pi.robot.mesh;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;

import com.pi.math.Vector3D;

public class BinarySTLLoader {
	ArrayList<MeshVertex> verticies;
	ArrayList<Integer> indicies;
	boolean mergeVerticies = true;

	private void readFacetB(ByteBuffer in, int index) throws IOException {
		Vector3D normal = new Vector3D(in.getFloat(), in.getFloat(),
				in.getFloat());
		for (int i = 0; i < 3; i++) {
			Vector3D pos = new Vector3D(in.getFloat(), in.getFloat(),
					in.getFloat());
			MeshVertex mv = new MeshVertex(pos, normal, new float[] { 0, 0 });
			int idx = -1;
			if (mergeVerticies) {
				int s = verticies.subList(Math.max(verticies.size() - 1000, 0),
						verticies.size()).lastIndexOf(mv);
				if (s >= 0) {
					idx = s + Math.max(verticies.size() - 1000, 0);
				}
			}
			if (idx < 0) {
				indicies.add(verticies.size());
				verticies.add(mv);
			} else {
				indicies.add(idx);
			}
		}
	}

	private void loadBinarySTL(File f) throws IOException {
		FileInputStream data;
		ByteBuffer dataBuffer;
		byte[] Info = new byte[80];
		byte[] Array_number = new byte[4];
		byte[] ioBuffer;
		int numberOfFaces;
		data = new FileInputStream(f);
		if (80 != data.read(Info)) {
			System.out.println("Format Error: 80 bytes expected");
		} else {
			data.read(Array_number);
			dataBuffer = ByteBuffer.wrap(Array_number);
			dataBuffer.order(ByteOrder.nativeOrder());
			numberOfFaces = dataBuffer.getInt();
			ioBuffer = new byte[50 * numberOfFaces];
			data.read(ioBuffer);
			dataBuffer = ByteBuffer.wrap(ioBuffer);
			dataBuffer.order(ByteOrder.nativeOrder());
			System.out.println("Number of faces= " + numberOfFaces);
			verticies = new ArrayList<MeshVertex>(numberOfFaces * 3);
			indicies = new ArrayList<Integer>(numberOfFaces * 3);
			int lastPercent = 0;
			for (int i = 0; i < numberOfFaces; i++) {
				try {
					int percent = (int) (i * 100 / numberOfFaces);
					if (percent > lastPercent) {
						System.out.println(percent);
					}
					lastPercent = percent;
					readFacetB(dataBuffer, i);
					if (i != numberOfFaces - 1) {
						dataBuffer.get();
						dataBuffer.get();
					}
				} catch (IOException e) {
					System.out.println("Format Error: iteration number " + i);
				}
			}
			indicies.trimToSize();
			verticies.trimToSize();
		}
		if (mergeVerticies) {
			System.out.println("Verticies: " + verticies.size()
					+ ", Indicies: " + indicies.size());
		}
		data.close();
	}

	public static Mesh loadSTL(File f) throws IOException {
		BinarySTLLoader loader = new BinarySTLLoader();
		loader.loadBinarySTL(f);
		return new Mesh(loader.verticies, loader.indicies, 3);
	}
}