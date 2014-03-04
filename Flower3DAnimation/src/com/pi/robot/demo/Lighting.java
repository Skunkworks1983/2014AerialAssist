package com.pi.robot.demo;

import java.nio.FloatBuffer;

import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;

public class Lighting {
	static FloatBuffer l0_position = (FloatBuffer) BufferUtils
			.createFloatBuffer(4)
			.put(new float[] { 0.0f, 1000.0f, 1000.0f, 0.0f }).rewind();
	static FloatBuffer ambient = (FloatBuffer) BufferUtils.createFloatBuffer(4)
			.put(new float[] { 0.125f, 0.125f, 0.125f, 1.0f }).rewind();
	static FloatBuffer l0_diffuse = (FloatBuffer) BufferUtils
			.createFloatBuffer(4)
			.put(new float[] { .125f, .125f, .125f, .125f }).rewind();
	static FloatBuffer l0_specular = (FloatBuffer) BufferUtils
			.createFloatBuffer(4)
			.put(new float[] { 0.125f, 0.125f, 0.125f, .125f }).rewind();

	public static void apply() {
		GL11.glLightModel(GL11.GL_AMBIENT, ambient);
		GL11.glLight(GL11.GL_LIGHT0, GL11.GL_POSITION, l0_position);
		GL11.glLight(GL11.GL_LIGHT0, GL11.GL_DIFFUSE, l0_diffuse);
		GL11.glLight(GL11.GL_LIGHT0, GL11.GL_SPECULAR, l0_specular);
	}

	public static void setup() {
		GL11.glEnable(GL11.GL_LIGHTING);
		GL11.glEnable(GL11.GL_COLOR_MATERIAL);
		GL11.glColorMaterial(GL11.GL_FRONT, GL11.GL_DIFFUSE);
		GL11.glMaterialf(GL11.GL_FRONT, GL11.GL_SHININESS, 64);
	}
}
