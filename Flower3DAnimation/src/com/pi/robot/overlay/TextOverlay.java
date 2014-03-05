package com.pi.robot.overlay;

import java.util.ArrayList;
import java.util.List;

import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Font;
import org.newdawn.slick.TrueTypeFont;

public class TextOverlay {
	private List<TimedMessage> messages = new ArrayList<TimedMessage>();
	private Font font;

	public TextOverlay() {
		messages.add(new TimedMessage("Test", -1));
	}

	public void addMessage(TimedMessage message) {
		this.messages.add(message);
	}

	public void renderOverlay(float width, float height) {
		if (font == null) {
			font = new TrueTypeFont(java.awt.Font.decode("Arial").deriveFont(
					14f), true);
		}
		float y = 0;
		float twidth = 0;
		for (TimedMessage m : messages) {
			twidth = Math.max(twidth, font.getWidth(m.getMessage()));
			y += font.getLineHeight();
		}
		GL11.glDisable(GL11.GL_LIGHTING);
		GL11.glDisable(GL11.GL_TEXTURE_2D);
		GL11.glDisable(GL11.GL_CULL_FACE);
		GL11.glColor4f(0f, 0f, 0f, 0.5f);
		GL11.glBegin(GL11.GL_QUADS);
		if (messages.size() > 0) {
			GL11.glVertex3f(0, 0, -0.0000001f);
			GL11.glVertex3f(twidth + 10, 0, -0.0000001f);
			GL11.glVertex3f(twidth + 10, y + 10, -0.0000001f);
			GL11.glVertex3f(0, y + 10, -0.0000001f);
		}
		GL11.glEnd();

		GL11.glEnable(GL11.GL_TEXTURE_2D);
		GL11.glColor3f(1f, 1f, 1f);
		y = 5;
		for (int i = messages.size() - 1; i >= 0; i--) {
			font.drawString(0, y, messages.get(i).getMessage());
			if (messages.get(i).isDead() || messages.size() - i > 5) {
				messages.remove(i);
			}
			y += font.getLineHeight();
		}

		GL11.glDisable(GL11.GL_TEXTURE_2D);
		GL11.glEnable(GL11.GL_LIGHTING);
	}
}
