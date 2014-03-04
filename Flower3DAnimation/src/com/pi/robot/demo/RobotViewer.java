package com.pi.robot.demo;

import java.io.File;
import java.io.IOException;

import org.lwjgl.LWJGLException;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.PixelFormat;

import com.pi.robot.Bone;
import com.pi.robot.Skeleton;
import com.pi.robot.overlay.TextOverlay;
import com.pi.robot.robot.RobotStateManager;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

public class RobotViewer {
	private static double horizontalTan = Math.tan(Math.toRadians(25));

	private int shaders;
	private TextOverlay textOverlay = new TextOverlay();
	int width = 768, height = 768;

	public RobotViewer() throws LWJGLException, IOException {
		NetworkTable.setTeam(1983);
		NetworkTable.setClientMode();
		NetworkTable.initialize();

		Skeleton sk = new Skeleton(new File("model/mesh.skl"));
		sk.calculate();
		RobotStateManager robot = new RobotStateManager(sk);

		init();

		Camera3rdPerson cam = new Camera3rdPerson();

		while (!Display.isCloseRequested()) {
			GL11.glClearColor(1f, 1f, 1f, 1f);
			GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);

			GL11.glMatrixMode(GL11.GL_PROJECTION);
			GL11.glLoadIdentity();
			double aspect = (double) height / (double) width;
			GL11.glFrustum(-horizontalTan, horizontalTan, aspect * -horizontalTan,
					aspect * horizontalTan, 1, 100000);
			GL11.glViewport(0, 0, width, height);
			
			GL11.glMatrixMode(GL11.GL_MODELVIEW);
			GL11.glLoadIdentity();

			cam.translate();
			GL11.glTranslatef(0, -25, 0);
			GL20.glUseProgram(shaders);
			Lighting.apply();

			drawBone(sk.getRootBone());

			Display.update();
			Display.sync(60);
			robot.update();
			Display.setTitle("Robot");
		}

		unloadBone(sk.getRootBone());
		GL20.glDeleteProgram(shaders);

	}

	private void overlay() {
		double aspect = ((double) height) / ((double) width);
		// Overlay
		GL11.glEnable(GL11.GL_TEXTURE_2D);
		GL11.glLoadIdentity();
		GL11.glTranslatef(-(float) horizontalTan,
				(float) (horizontalTan * aspect), -1);
		GL11.glScalef((float) horizontalTan / width * 2f,
				-(float) horizontalTan / width * 2f, 1);
		// GL11.glRotatef(180, 1, 0, 0);
		textOverlay.renderOverlay(width, height);
		GL11.glDisable(GL11.GL_TEXTURE_2D);
	}

	private void unloadBone(Bone b) {
		if (b.mesh != null) {
			b.mesh.unloadFromGPU();
		}
		for (Bone s : b.getChildren()) {
			drawBone(s);
		}
	}

	private void drawBone(Bone b) {
		b.draw();
		for (Bone s : b.getChildren()) {
			drawBone(s);
		}
	}

	private void init() throws LWJGLException {
		Display.setDisplayMode(new DisplayMode(width, height));
		Display.create(new PixelFormat(0, 8, 0, 4));

		Lighting.setup();

		GL11.glEnable(GL11.GL_DEPTH_TEST);
		GL11.glShadeModel(GL11.GL_SMOOTH);
		GL11.glEnable(GL11.GL_LIGHT0);
		GL11.glEnable(GL11.GL_BLEND);
		GL11.glEnable(GL11.GL_CULL_FACE);
		GL11.glCullFace(GL11.GL_BACK);
		GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);
		shaders = ShaderLoader.loadShaderPair();
	}

	public static void main(String[] args) throws LWJGLException, IOException {
		new RobotViewer();
	}
}
