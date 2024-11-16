#pragma once
#include<graphics.h>
#include"vector2.h"
#include"Camera.h"
#pragma comment(lib,"MSIMG32.LIB")
#include<iostream>

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	if (img == nullptr) {
		std::cerr << "Error: img is nullptr in putimage_alpha at position ("
			<< dst_x << ", " << dst_y << ")" << std::endl;
		return;
	}

	int w = img->getwidth();
	int h = img->getheight();

	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
	if (img == nullptr) {
		std::cerr << "Error: img is nullptr in putimage_alpha at position ("
			<< dst_x << ", " << dst_y << ")" << std::endl;
		return;
	}

	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos_camera = camera.get_position();
	if (w <= 0 || h <= 0) {
		std::cerr << "Error: Invalid image dimensions (" << w << "x" << h
			<< ") in putimage_alpha at position (" << dst_x << ", " << dst_y << ")" << std::endl;
		return;
	}

	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y)
{
	int w = width > 0 ? width : img->getwidth();
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void line(const Camera& camera, int x1, int y1, int x2, int y2)
{
	const Vector2& pos_camera = camera.get_position();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

//用于水平翻转图片
inline void flip_image(IMAGE* src, IMAGE* dst)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int index_src = y * w + x;
			int index_dst = y * w + (w - x - 1);
			dst_buffer[index_dst] = src_buffer[index_src];
		}
	}

}

//用于将图片处理为纯白色剪影
inline void sketch_image(IMAGE* src, IMAGE* dst)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int index = y * w + x;
			dst_buffer[index] = BGR(RGB(255, 255, 255) | (src_buffer[index] & 0xFF000000));
		}
	}
	
}