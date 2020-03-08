# FT232EEPFlash

FT232EEPFlash
====
FT232シリーズのEEPROMを読み込み及び書き換えるツールです。

## Description
FT232シリーズは純正ツールのFT_Progがありますが、EEPROM上全ての領域を操作できる訳ではありません。
そのため、「間違えて書き込んじゃった！！」(不可逆な操作)
が平然と起こり得るわけです。

これを防ぐために、本ツールを使い以下のユースケースを想定しています。
・FT232シリーズのEEPROMのバックアップ
・FT232シリーズのEEPROMの復元

## Demo
![](https://i.gyazo.com/ade2d827591d94756a89c95eb6274532.gif)

## Example
・FT232上のEEPROMを読み出してファイル(filename.bin)に書き込む
>FT232EEPFlash.exe filename.bin -r

・バイナリファイル(binary.bin)をFT232上のEEPROMに書き込み
>FT232EEPFlash.exe binary.bin -w

## VS. 
libftdi1 ftdi-eeprom と類似しています。
libftdi1はLinuxで使うことを想定されているため、Windows環境で使うのは大変です。

一方で、こちらはWindowsをターゲットとして開発しています。

## Install
VS2015で開発しています。適当にビルドしてください。
gccやその他ツールでのBuildは未確認ですごめんなさい。

## Licence
MITにしたいけどちょっとFTDIのLibがどうなってるか詳しくわからないからまだあやふやで。

## Note
・Typoしたりすると非常に高圧的な態度で指摘してきますが、
私が「親に向かってなんだその態度は！！！」と怒って遊ぶためにそうなってるので気にしないでください。
飽きてきたら普通にします。
