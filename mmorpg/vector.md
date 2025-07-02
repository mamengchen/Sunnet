主要讨论的是push_back 和 emplace_back:

<p size="2">在后面的优化：push_back 工作方式：<br>
1.接受一个已构造好的对象（左值和右值）。<br>
2.通过拷贝或者移动构造函数添加到容器尾部。
</p>

<p size="2">
emplace_back 工作方式：<br>
1.接受构造对象所需的参数列表。<br>
2.直接在容器内存中构造对象（完美转发参数），避免临时对象。
</p>

``` C++
// 左值版本 (const T& value)
void push_back(const T& value) {
    if (size_ >= capacity_) {
        reserve(capacity_ * 2); // 扩容逻辑（通常翻倍）
    }
    // 在尾部内存位置拷贝/移动构造对象
    allocator_traits::construct(allocator_, data_ + size_, value);
    ++size_;
}

// 右值版本 (T&& value)
void push_back(T&& value) {
    if (size_ >= capacity_) {
        reserve(capacity_ * 2);
    }
    // 移动构造对象
    allocator_traits::construct(allocator_, data_ + size_, std::move(value));
    ++size_;
}

-- emplace_back
template <typename... Args>
reference emplace_back(Args&&... args) {
    if (size_ >= capacity_) {
        reserve(capacity_ * 2);
    }
    // 直接在尾部内存位置构造对象
    allocator_traits::construct(
        allocator_, 
        data_ + size_, 
        std::forward<Args>(args)... // 完美转发参数
    );
    ++size_;
    return data_[size_ - 1]; // 返回新对象的引用
}
```