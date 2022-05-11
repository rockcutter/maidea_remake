# maidea

maideaはあったら便利な機能を詰め込んだ、C++で書かれたdiscord botです。
SleepyDiscordライブラリをdiscord APIのラッパーとして使用しています。
[SleepyDiscord](https://yourwaifu.dev/sleepy-discord/)
また、Boostライブラリも使用しています
それぞれの機能をmoduleとして実装しており、容易に機能の追加が可能です

# Features
slash commandを実装しており、/をこのbotが導入されているdiscordサーバで入力することで機能を使用することができる
また、discordサーバーで次のような発言をすると、それぞれのmoduleの機能が利用できる
```
>[command] [オプション]
![command] [オプション]
\[command] [オプション]
?[command] [オプション]
```
  
# Requirement
* cmake
* boost 1.79.0
* SleepyDiscord
 
# Installation
boost 
https://boostjp.github.io/howtobuild.html などを参考にインストールしておく

SleepyDiscord
https://yourwaifu.dev/sleepy-discord/docs/ に従い必要なライブラリのインストール& git cloneしておく

```bash
projectDir# git clone https://github.com/rockcutter/maidea_remake
projectDir# mkdir bld
projectDir# cd bld
projectDir/bld# cmake ../
projectDir/bld# make
projectDir/bld# ./maidea
```

# モジュールの作成  
src/module/example/ExampleModule.hにあるモジュールのプロトタイプを使用して作成してください

