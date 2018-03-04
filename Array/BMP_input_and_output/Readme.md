# BMP 讀寫

這份 code 的功能是，讀取 BMP 圖檔，將 RGB 彩色圖像轉成 Graylevel 灰階圖像，再輸出灰階的 BMP 圖檔。

在輸入時，會處理兩種輸入： `32bit (rgba)` 和 `24bit (rgb)`。

在輸出時，會使用 padding 處理 `4-byte alignment`。

## 經由這份 Code 我學到...

* 使用 C 語言處理 BMP 圖檔的輸出入
* 如何宣告及釋放二維陣列
* 使用不同方法讀取輸入檔名
* bitwise operation
* 自定義 struct 來代表 BMP 圖檔，如 opencv 的 iplimage。
