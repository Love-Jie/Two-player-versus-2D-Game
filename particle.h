#pragma once
#include"Atlas.h"
#include"Vector2.h"
#include"Util.h"
#include"Camera.h"

class Particle
{
public:
	Particle() = default;
	~Particle() = default;

	Particle(const Vector2& position, Atlas* atlas, int lifespan)
		:position(position), atlas(atlas), lifespan(lifespan) {}

	void on_update(int delta)
	{
		timer += delta;
		if (timer >= lifespan)
		{
			timer = 0;
			index_frame++;
			if (index_frame >= atlas->get_size())
			{
				index_frame = atlas->get_size() - 1;
				valid = false;
			}
			
		}
	}

	void on_draw(const Camera& camera) const
	{
		putimage_alpha(camera, (int)position.x, (int)position.y, atlas->get_image(index_frame));
	}
	
	void set_atlas(Atlas* new_atlas)
	{
		atlas = new_atlas;
	}

	void set_position(const Vector2& new_position)
	{
		position = new_position;
	}

	void set_lifespan(int ms)
	{
		lifespan = ms;
	}

	bool check_valid() const
	{
		return valid;
	}

private:
	int timer = 0;			//���Ӷ������Ŷ�ʱ��
	int lifespan = 0;		//��֡���Ӷ�������ʱ��
	int index_frame = 0;	//��ǰ���ڲ��ŵĶ���֡
	Vector2 position;		//���ӵ���������
	bool valid = true;		//���Ӷ����Ƿ���Ч
	Atlas* atlas = nullptr; //���Ӷ�����ʹ�õ�ͼ��
};