package com.pi.robot.demo;

import java.io.File;
import java.io.IOException;
import java.nio.FloatBuffer;
import java.util.HashMap;
import java.util.Map;

import org.lwjgl.BufferUtils;
import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;

import com.pi.math.Vector3D;
import com.pi.robot.Bone;
import com.pi.robot.Skeleton;
import com.pi.robot.robot.MotorState;
import com.pi.robot.robot.NotificationBubble;
import com.pi.robot.robot.RobotStateManager;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

public class RobotViewer {
	private static double horizontalTan = Math.tan(Math.toRadians(25));
	static FloatBuffer l0_position = (FloatBuffer) BufferUtils
			.createFloatBuffer(4).put(new float[] { 0.0f, 1.0f, 1.0f, 0.0f })
			.rewind();
	static FloatBuffer l0_ambient = (FloatBuffer) BufferUtils
			.createFloatBuffer(4).put(new float[] { 0.5f, 0.5f, 0.5f, 1.0f })
			.rewind();
	static FloatBuffer l0_diffuse = (FloatBuffer) BufferUtils
			.createFloatBuffer(4).put(new float[] { .25f, .25f, .25f, .25f })
			.rewind();
	static FloatBuffer l0_specular = (FloatBuffer) BufferUtils
			.createFloatBuffer(4).put(new float[] { 0.25f, 0.25f, 0.25f, 1f })
			.rewind();
	boolean[] keys = new boolean[512];
	Map<Vector3D, NotificationBubble> notifications = new HashMap<Vector3D, NotificationBubble>();

	public RobotViewer() throws LWJGLException, IOException {
		NetworkTable.setTeam(1983);
		NetworkTable.setClientMode();
		NetworkTable.initialize();

		Skeleton sk = new Skeleton(new File("model/mesh.skl"));
		sk.calculate();
		RobotStateManager robot = new RobotStateManager(sk, notifications);

		init();

		Camera3rdPerson cam = new Camera3rdPerson();

		while (!Display.isCloseRequested()) {
			GL11.glClearColor(1f, 1f, 1f, 1f);
			GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);

			GL11.glMatrixMode(GL11.GL_MODELVIEW);
			GL11.glLoadIdentity();

			cam.translate();
			GL11.glTranslatef(0, -25, 0);
			GL11.glLight(GL11.GL_LIGHT0, GL11.GL_AMBIENT, l0_ambient);
			GL11.glLight(GL11.GL_LIGHT0, GL11.GL_POSITION, l0_position);
			GL11.glLight(GL11.GL_LIGHT0, GL11.GL_DIFFUSE, l0_diffuse);
			GL11.glLight(GL11.GL_LIGHT0, GL11.GL_SPECULAR, l0_specular);

			drawBone(sk.getRootBone());

			for (NotificationBubble b : notifications.values()) {
				b.render();
			}

			Display.update();
			Display.sync(60);
			boolean[] oldKeys = new boolean[512];
			System.arraycopy(keys, 0, oldKeys, 0, oldKeys.length);

			if ((keys[Keyboard.KEY_C] = Keyboard.isKeyDown(Keyboard.KEY_C))
					&& !oldKeys[Keyboard.KEY_C]) {
				robot.hasBall = !robot.hasBall;
			}
			if ((keys[Keyboard.KEY_J] = Keyboard.isKeyDown(Keyboard.KEY_J))
					&& !oldKeys[Keyboard.KEY_J]) {
				robot.jawsClosed = !robot.jawsClosed;
			}
			if ((keys[Keyboard.KEY_V] = Keyboard.isKeyDown(Keyboard.KEY_V))
					&& !oldKeys[Keyboard.KEY_V]) {
				robot.collectorState.setState(MotorState
						.decode(robot.collectorState.getState().ordinal() + 1));
			}
			if (Keyboard.isKeyDown(Keyboard.KEY_U)) {
				robot.pterodactylAngle += 0.01;
			}
			if (Keyboard.isKeyDown(Keyboard.KEY_I)) {
				robot.pterodactylAngle -= 0.01;
			}
			if (Keyboard.isKeyDown(Keyboard.KEY_O)) {
				robot.shooterAngle += 0.01;
			}
			if (Keyboard.isKeyDown(Keyboard.KEY_P)) {
				robot.shooterAngle -= 0.01;
			}
			robot.update();
			Display.setTitle("Robot");
		}
	}

	public void drawBone(Bone b) {
		if (false) {
			GL11.glColor3f(1f, 0f, 0f);
			GL11.glBegin(GL11.GL_LINES);
			GL11.glVertex3f(b.getBoneStart().x, b.getBoneStart().y,
					b.getBoneStart().z);
			GL11.glVertex3f(b.getBoneEnd().x, b.getBoneEnd().y,
					b.getBoneEnd().z);
			GL11.glEnd();
		}
		b.draw();
		for (Bone s : b.getChildren()) {
			drawBone(s);
		}
	}

	public void init() throws LWJGLException {
		Display.setDisplayMode(new DisplayMode(768, 768));
		Display.create();

		GL11.glMatrixMode(GL11.GL_PROJECTION);
		GL11.glLoadIdentity();
		double aspect = 1f;
		GL11.glFrustum(-horizontalTan, horizontalTan, aspect * -horizontalTan,
				aspect * horizontalTan, 1, 100000);
		// GL11.glOrtho(-256, 256, -256, 256, -1000, 1000);
		// GL11.glPolygonMode(GL11.GL_FRONT_AND_BACK, GL11.GL_LINE);

		GL11.glEnable(GL11.GL_LIGHTING);
		GL11.glEnable(GL11.GL_COLOR_MATERIAL);
		GL11.glEnable(GL11.GL_DEPTH_TEST);
		GL11.glShadeModel(GL11.GL_SMOOTH);
		GL11.glEnable(GL11.GL_LIGHT0);
		GL11.glEnable(GL11.GL_BLEND);
		GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);
	}

	public static void main(String[] args) throws LWJGLException, IOException {
		new RobotViewer();
	}
}
