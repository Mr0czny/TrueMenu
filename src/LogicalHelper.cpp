

bool isInRect(int pointX, int pointY, int rectX, int rectY, int width, int height) {
	return pointX < rectX + width && pointX >= rectX && pointY < rectY + height && pointY >= rectY;
}