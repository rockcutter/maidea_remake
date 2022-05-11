#src/module/example
#ライブラリを作成する 
add_library([ライブラリ名] STATIC [ソースファイル])

#EssentialにはSleepyDiscordとboostのヘッダが含まれる
target_link_libraries([ライブラリ名] PRIVATE Essential)

#次にsrc/module/CMakeLists.txtを書き換える