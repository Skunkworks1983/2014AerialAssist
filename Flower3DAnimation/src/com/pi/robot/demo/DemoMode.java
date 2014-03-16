package com.pi.robot.demo;

import com.pi.math.Vector3D;
import com.pi.robot.Bone;
import com.pi.robot.Skeleton;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

public class DemoMode {
	public static void movePtero(NetworkTable table, float target)
			throws Exception {
		double curr = table.getNumber("pterodactylAngle", 0);
		do {
			double next = curr
					+ (Math.abs(target - curr) > 2.5 ? (Math.signum(target
							- curr) * 2.5) : (target - curr));
			table.putNumber("pterodactylAngle", next);
			curr = next;
			Thread.sleep(50L);
		} while (Math.abs(curr - target) > 2.5);
	}

	public static void moveShooter(NetworkTable table, float target)
			throws Exception {
		double curr = table.getNumber("shooterStrap", 0);
		do {
			double next = curr
					+ (Math.abs(target - curr) > 0.025 ? Math.signum(target
							- curr) * 0.025 : (target - curr));
			table.putNumber("shooterStrap", next);
			curr = next;
			Thread.sleep(50L);
		} while (Math.abs(curr - target) > 0.03);
	}

	public static void tweenBall(Skeleton sk, Vector3D target, float speed)
			throws InterruptedException {
		Bone ball = sk.getBone(5);
		if (ball != null) {
			do {
				ball.additional.x = ball.additional.x
						+ (Math.abs(target.x - ball.additional.x) > speed ? Math
								.signum(target.x - ball.additional.x) * speed
								: (target.x - ball.additional.x));
				ball.additional.y = ball.additional.y
						+ (Math.abs(target.y - ball.additional.y) > speed ? Math
								.signum(target.y - ball.additional.y) * speed
								: (target.y - ball.additional.y));
				ball.additional.z = ball.additional.z
						+ (Math.abs(target.z - ball.additional.z) > speed ? Math
								.signum(target.z - ball.additional.z) * speed
								: (target.z - ball.additional.z));
				Thread.sleep(50L);
			} while (Math.abs(ball.additional.x - target.x) > 0.01
					|| Math.abs(ball.additional.y - target.y) > 0.01
					|| Math.abs(ball.additional.z - target.z) > 0.01);
		}
	}

	public static void startDemoMode(final NetworkTable table, final Skeleton sk) {
		new Thread(new Runnable() {
			public void run() {
				while (true) {
					try {
						table.putNumber("alliance",
								((int) table.getNumber("alliance", 0)) ^ 0);
						// Reset shooter
						System.out.println("resetting shooter");
						moveShooter(table, 0);
						table.putBoolean("shooterLatched", true);
						table.putNumber("shooterStrap", 1.1);

						// Collect pos
						System.out.println("Move ptero");
						movePtero(table, 0);

						// Collect
						System.out.println("Collect");
						table.putNumber("collectorMotorState", 1);
						table.putBoolean("jawsClosed", true);

						Thread.sleep(1500);
						table.putNumber("collectorMotorState", 0);
						Bone ball = sk.getBone(5);
						if (ball != null) {
							ball.additional = new Vector3D(30, 0, 0);
						}
						table.putBoolean("hasBall", true);
						tweenBall(sk, new Vector3D(0f, 0f, 0f), 1.5f);

						// Carry pos
						System.out.println("Move ptero");
						movePtero(table, 90);

						// Move the drivebase
						table.putNumber("driveLeftState", 1);
						table.putNumber("driveRightState", 1);
						Thread.sleep(1500);

						// Shoot pos
						table.putNumber("driveLeftState", 0);
						table.putNumber("driveRightState", 0);
						movePtero(table, 75);
						table.putBoolean("jawsClosed", false);
						Thread.sleep(500);
						if (ball != null) {
							ball.lockTransform(true);
						}
						Thread.sleep(250L);
						table.putBoolean("shooterLatched", false);
						tweenBall(sk, new Vector3D(100f, 0f, 0f), 10f);
						table.putBoolean("hasBall", false);
						Thread.sleep(500L);
						if (ball != null) {
							ball.lockTransform(false);
						}
						Thread.sleep(500L);
					} catch (Exception e) {
					}
				}
			}
		}).start();
	}
}
