#pragma once
#include"Vector2.h"
#include"Timer.h"

class Camera
{
public:
	Camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_callback(
			[&]()
			{
				is_shaking = false;
				reset();
			}
		);
	
	}
	~Camera() = default;

	//摄像机抖动方法
	void shake(float strength, int duration)
	{
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}

	const Vector2& get_position() const
	{
		return position;
	}

	void reset()
	{
		position.x = 0;
		position.y = 0;
	}

	void on_update(int delta)
	{
		timer_shake.on_update(delta);

		if (is_shaking)
		{
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

private:
	Vector2 position;			 //摄像机位置
	Timer timer_shake;				 //摄像机抖动定时器
	bool is_shaking = false;	 //摄像机是否抖动
	float shaking_strength = 0;  //摄像机抖动幅度
};