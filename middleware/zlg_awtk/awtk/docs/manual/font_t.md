## font\_t
### 概述
 代表一种字体。


----------------------------------
### 函数
<p id="font_t_methods">

| 函数名称 | 说明 | 
| -------- | ------------ | 
| <a href="#font_t_font_destroy">font\_destroy</a> | 销毁font对象。 |
| <a href="#font_t_font_get_baseline">font\_get\_baseline</a> | 获取字体的基线。 |
| <a href="#font_t_font_get_glyph">font\_get\_glyph</a> | 获取指定字符和大小的字模。 |
| <a href="#font_t_font_match">font\_match</a> | 检查当前字体是否与指定名称和大小相匹配。 |
#### font\_destroy 函数
-----------------------

* 函数功能：

> <p id="font_t_font_destroy"> 销毁font对象。



* 函数原型：

```
ret_t font_destroy (font_t* font);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败。 |
| font | font\_t* | font对象。 |
#### font\_get\_baseline 函数
-----------------------

* 函数功能：

> <p id="font_t_font_get_baseline"> 获取字体的基线。



* 函数原型：

```
int32_t font_get_baseline (font_t* font, font_size_t font_size);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | int32\_t | 返回字体的基线。 |
| font | font\_t* | font对象。 |
| font\_size | font\_size\_t | 字体大小。 |
#### font\_get\_glyph 函数
-----------------------

* 函数功能：

> <p id="font_t_font_get_glyph"> 获取指定字符和大小的字模。




* 函数原型：

```
ret_t font_get_glyph (font_t* font, wchar_t chr, font_size_t font_size, glyph_t* glyph);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败。 |
| font | font\_t* | font对象。 |
| chr | wchar\_t | 字符。 |
| font\_size | font\_size\_t | 字体大小。 |
| glyph | glyph\_t* | 返回字模数据。 |
#### font\_match 函数
-----------------------

* 函数功能：

> <p id="font_t_font_match"> 检查当前字体是否与指定名称和大小相匹配。




* 函数原型：

```
int32_t font_match (font_t* font, const char* font_name, font_size_t font_size);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | int32\_t | 返回TRUE表示成功，FALSE表示失败。 |
| font | font\_t* | font对象。 |
| font\_name | const char* | 字体名称。 |
| font\_size | font\_size\_t | 字体大小。 |
