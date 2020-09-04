# 音乐信息表



| 路径/文件名              | 功能               |
| ------------------------ | ------------------ |
| sound/sem/zombie-eat.wav | 僵尸吃植物的声音   |
| sound/sem/hit-1.mp3      | 豌豆打到僵尸的声音 |
| sound/sem/shoot.wav      | 豌豆发出的声音     |
| sound/sem/boom.mp3       | 辣椒、樱桃爆炸     |
| sound/sem/victory.wav    | 游戏胜利的声音     |
| sound/sem/defeat.mp3     | 游戏失败的声音     |
| sound/sem/game-over.wav  | 僵尸进入家门       |
|                          |                    |
| sound/ui/click1.wav      | 点击声音1          |
| sound/ui/click1.wav      | 点击声音2          |
|                          |                    |
| sound/bgm/b-day.mp3      | 白天背景音乐1      |
| sound/bgm/Day.mp3        | 白天背景音乐2      |
| sound/bgm/Faster.mp3     | 背景音乐快速版     |
| sound/bgm/Night.mp3      | 夜晚背景音乐       |
|                          |                    |
|                          |                    |
|                          |                    |
|                          |                    |



### 关于添加音乐

音乐复制到 `Bin/sound` 文件夹，参照 `pvzConfig.ini` 其他示例

### 关于使用音乐

`SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");`



<hr>

注：全局循环背景音乐必须为mp3格式