# maidea

maideaはあったら便利な機能を詰め込んだ、C++で書かれたdiscord botです。
SleepyDiscordライブラリをdiscord APIのラッパーとして使用しています。
[SleepyDiscord](https://yourwaifu.dev/sleepy-discord/)
また、Boostライブラリも使用しています
それぞれの機能をmoduleとして実装しており、容易に機能の追加が可能です

# Features

このbotが導入されているdiscordサーバーで次のような発言をすると、それぞれのmoduleの機能が利用できる
```
>[command] [オプション]
![command] [オプション]
\\[command] [オプション]
?[command] [オプション]
```
  
## Module一覧
ほとんどのモジュールにはヘルプオプション(-h)が実装されている
- Hello
Helloモジュールはコマンドを実行するとHelloと返す  
example
```
>hello
```
result
```
Hello
Hello!
```
- Timer

Timerモジュールはオプションで秒(-s)、時間(-o)、日(-d)を指定してタイマーをセットする    
オプションなしで分でタイマーをセットする  
example
```
#
>timer -m 20 
```
result
```
Timer
20分タイマーをセット!
```
