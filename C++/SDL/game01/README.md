# SDL2 贪吃蛇游戏

## 文件说明
- `snake.cpp`：贪吃蛇游戏主程序，基于SDL2开发。

## 编译方法

1. 安装SDL2开发库（Windows建议用vcpkg、MSYS2或官网下载开发包）。
2. 使用如下命令编译（假设SDL2已配置好环境变量）：

```
g++ snake.cpp -o snake.exe -lSDL2
```

如未配置环境变量，请指定SDL2头文件和库文件路径，例如：

```
g++ snake.cpp -IC:/SDL2/include -LC:/SDL2/lib -lSDL2 -o snake.exe
```

## 运行方法

```
snake.exe
```

## 操作说明
- 方向键控制蛇移动
- ESC退出游戏 