package com.pi.robot.robot;

import com.pi.math.Quaternion;
import com.pi.math.TransMatrix;
import com.pi.math.Vector3D;
import com.pi.robot.Skeleton;
import com.pi.robot.mesh.FloatBufferColor;
import com.pi.robot.mesh.Mesh;
import com.pi.robot.mesh.MeshVertex;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.tables.ITable;

public class RobotStateManager {
	public static final int BALL_ID = 5;
	public static final int CATAPULT_ID = 4;
	public static final int JAWS_ID = 3;
	public static final int PTERODACTYL_ID = 2;
	public static final int DRIVEBASE_ID = 0;
	public static final int TOPPER_ID = 1;
	public static final FloatBufferColor defaultColor = new FloatBufferColor(
			0.75f, 0.75f, 0.75f);
	private static final FloatBufferColor NOTIFICATION_STALL_COLOR = new FloatBufferColor(
			1f, 0f, 0f, 0.125f);

	private Skeleton sk;

	public Changeable<Alliance> alliance = new Changeable<Alliance>(
			Alliance.INVALID);
	public boolean hasBall;
	public boolean jawsClosed;

	public float pterodactylAngle = 0;
	public Changeable<MotorState> collectorState = new Changeable<MotorState>(
			MotorState.OFF);

	public float shooterAngle = 0;
	public Changeable<MotorState> winchState = new Changeable<MotorState>(
			MotorState.OFF);

	public Changeable<MotorState> compressorState = new Changeable<MotorState>(
			MotorState.OFF);
	public Changeable<MotorState> driveLeftState = new Changeable<MotorState>(
			MotorState.OFF);
	public Changeable<MotorState> driveRightState = new Changeable<MotorState>(
			MotorState.OFF);

	public Vector3D winchNotificationPos = new Vector3D(-0.625f, 0.125f, -3.0f);

	private float currentPterodactylAngle = 0;
	private float targetJawsAngle = 0;
	private float currentJawsAngle = 0;
	private ITable table;

	public RobotStateManager(Skeleton sk) {
		this.sk = sk;
		table = NetworkTable.getTable("Robot");
	}

	private void colorAlliance(FloatBufferColor color) {
		if (sk.getBone(BALL_ID) != null) {
			for (MeshVertex vv : sk.getBone(BALL_ID).mesh.getVerticies()) {
				vv.setColor(color);
			}
			sk.getBone(BALL_ID).mesh.generateBuffers();
			sk.getBone(BALL_ID).mesh.loadToGPU();
		}
	}

	private void colorMesh(FloatBufferColor motorColor, Mesh mesh,
			Vector3D min, Vector3D max, TransMatrix bleh) {
		Vector3D base = min.clone().add(max).multiply(.5f);
		min.subtract(base);
		max.subtract(base);
		if (mesh != null) {
			for (MeshVertex vv : mesh.getVerticies()) {
				Vector3D test = vv.getPosition().clone().subtract(base);
				if (bleh != null) {
					test = bleh.multiply(test);
				}
				if (test.inside(min, max)) {
					vv.setColor(motorColor);
				}
			}
			mesh.generateBuffers();
			mesh.loadToGPU();
		}
	}

	private void colorWinchMotor(FloatBufferColor motorColor) {
		if (sk.getBone(PTERODACTYL_ID) == null
				|| sk.getBone(PTERODACTYL_ID).mesh == null) {
			return;
		}
		Vector3D min = new Vector3D(-2.75f, -.75f, -6f);
		Vector3D max = new Vector3D(1.5f, 1f, 0f);
		colorMesh(motorColor, sk.getBone(PTERODACTYL_ID).mesh, min, max, null);
	}

	private void colorCollectorMotor(FloatBufferColor motorColor) {
		if (sk.getBone(JAWS_ID) == null) {
			return;
		}
		Vector3D min = new Vector3D(-3.91f, -6.1f, 24f);
		Vector3D max = new Vector3D(0f, 6.1f, 25.76f);
		TransMatrix bleh = new TransMatrix().setRotation(0f, 1f, 0f, -33f
				* (float) Math.PI / 180.0f);
		colorMesh(motorColor, sk.getBone(JAWS_ID).mesh, min, max, bleh);
	}

	private void colorCompressor(FloatBufferColor compressorColor) {
		if (sk.getBone(DRIVEBASE_ID) == null
				|| sk.getBone(DRIVEBASE_ID).mesh == null) {
			return;
		}
		Vector3D min = new Vector3D(6, -1.1f, 1.2f);
		Vector3D max = new Vector3D(11.5f, 1.1f, 6f);
		colorMesh(compressorColor, sk.getBone(DRIVEBASE_ID).mesh, min, max,
				null);
	}

	private void colorDriveMotor(FloatBufferColor compressorColor, boolean left) {
		if (sk.getBone(DRIVEBASE_ID) == null
				|| sk.getBone(DRIVEBASE_ID).mesh == null) {
			return;
		}
		Vector3D min = new Vector3D(4, left ? 1.4f : -6f, 3.5f);
		Vector3D max = new Vector3D(11.5f, left ? 6f : -1.4f, 8);
		colorMesh(compressorColor, sk.getBone(DRIVEBASE_ID).mesh, min, max,
				null);
	}

	private void updateJaws() {
		if (sk.getBone(JAWS_ID) == null) {
			return;
		}

		if (jawsClosed) {
			targetJawsAngle = hasBall ? (float) Math.PI / 8f
					: (float) Math.PI / 10f;
		} else {
			targetJawsAngle = (float) Math.PI / 5f;
		}

		if (hasBall && currentJawsAngle < (float) Math.PI / 8f) {
			currentJawsAngle = (float) Math.PI / 8f;
		}

		sk.getBone(JAWS_ID).slerp(new Quaternion(0f, (float) 0f, 0f),
				new Quaternion(0.0f, (float) -1.0f, 0.0f), currentJawsAngle);
		float diffA = Math.signum(targetJawsAngle - currentJawsAngle) * 0.1f;
		if (diffA > 0) {
			diffA *= 0.05f;
		}
		float diffB = targetJawsAngle - currentJawsAngle;
		currentJawsAngle += Math.abs(diffA) < Math.abs(diffB) ? diffA : diffB;
	}

	private void updatePterodactyl() {
		if (sk.getBone(PTERODACTYL_ID) == null) {
			return;
		}

		sk.getBone(PTERODACTYL_ID).slerp(new Quaternion(0f, (float) 0f, 0f),
				new Quaternion(0.0f, (float) 1.0f, 0.0f),
				(float) (Math.PI / 1.75) - currentPterodactylAngle);
		float diffA = Math.signum(pterodactylAngle - currentPterodactylAngle) * 0.1f;
		float diffB = pterodactylAngle - currentPterodactylAngle;
		currentPterodactylAngle += Math.abs(diffA) < Math.abs(diffB) ? diffA
				: diffB;
	}

	private void updateMotors() {
		if (collectorState.hasChanged()) {
			colorCollectorMotor(collectorState.getState().getColor());
		}
		if (winchState.hasChanged() && sk.getBone(PTERODACTYL_ID) != null) {
			colorWinchMotor(winchState.getState().getColor());
			if (winchState.getState() == MotorState.STALLED) {
				// Icky icky TODO
				sk.getBone(PTERODACTYL_ID).notifications.put(
						winchNotificationPos, new NotificationBubble(
								winchNotificationPos, NOTIFICATION_STALL_COLOR,
								5));
			} else {
				sk.getBone(PTERODACTYL_ID).notifications
						.remove(winchNotificationPos);
			}
		}
	}

	private void updateShooter() {
		if (sk.getBone(CATAPULT_ID) != null) {
			sk.getBone(CATAPULT_ID).slerp(new Quaternion(0f, (float) 0f, 0f),
					new Quaternion(0.0f, (float) 1.0f, 0.0f),
					shooterAngle - (float) Math.PI / 3f);
		}
	}

	public void update() {
		hasBall = table.getBoolean("hasBall", false);
		jawsClosed = table.getBoolean("jawsClosed", false);
		pterodactylAngle = (float) (table.getNumber("pterodactylAngle", 0)
				* Math.PI / 180.0f);
		collectorState.setState(MotorState.decode((int) table.getNumber(
				"collectorMotorState", 0)));
		alliance.setState(Alliance.decode((int) table.getNumber("alliance", 2)));

		shooterAngle = table.getBoolean("shooterLatched", false) ? 0
				: (float) table.getNumber("shooterStrap", 0) * (float) Math.PI
						/ 2.0f;
		winchState.setState(MotorState.decode((int) table.getNumber(
				"winchMotorState", 0)));

		compressorState.setState(MotorState.decode((int) table.getNumber(
				"compressorState", 0)));
		driveLeftState.setState(MotorState.decode((int) table.getNumber(
				"driveLeftState", 0)));
		driveRightState.setState(MotorState.decode((int) table.getNumber(
				"driveRightState", 0)));

		if (sk.getBone(BALL_ID) != null) {
			sk.getBone(BALL_ID).visible = hasBall;
		}
		updateJaws();
		updatePterodactyl();
		updateMotors();
		updateShooter();
		updateDrivebase();
		sk.calculate();

		if (alliance.hasChanged()) {
			colorAlliance(alliance.getState().getColor());
		}
	}

	private void updateDrivebase() {
		if (compressorState.hasChanged()) {
			colorCompressor(compressorState.getState().getColor());
		}
		if (driveLeftState.hasChanged()) {
			colorDriveMotor(driveLeftState.getState().getColor(), true);
		}
		if (driveRightState.hasChanged()) {
			colorDriveMotor(driveRightState.getState().getColor(), false);
		}
	}
}
