#pragma once

#include <vector>
#include <memory>
#include <graphics.h>

class Atlas
{
public:
    Atlas() = default;
    ~Atlas() = default;

    bool load_from_file(LPCTSTR path_template, int num)
    {
        clear();
        img_list.reserve(num);
        //img_list.resize(num);     // 调整大小以确保可以安全访问

        TCHAR path_file[256];
        for (int i = 0; i < num; i++)
        {
            auto img = std::make_unique<IMAGE>();
            _stprintf_s(path_file, path_template, i + 1);

            loadimage(img.get(), path_file);
            img_list.push_back(std::move(img));
            
        }
        return true;
    }

    void clear()
    {
        img_list.clear();
    }

    int get_size() const
    {
        return static_cast<int>(img_list.size());
    }

    IMAGE* get_image(int index)
    {
        if (index < 0 || index >= img_list.size())
        {
            return nullptr;
        }
        return img_list[index].get();  // 返回指针
    }

    void add_image(std::unique_ptr<IMAGE>img)
    {
        img_list.push_back(std::move(img));
    }

private:
    std::vector<std::unique_ptr<IMAGE>> img_list;
};
