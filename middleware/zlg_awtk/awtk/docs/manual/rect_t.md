## rect\_t
### 概述
 矩形。包括一个x坐标、y坐标、宽度和高度。

----------------------------------
### 函数
<p id="rect_t_methods">

| 函数名称 | 说明 | 
| -------- | ------------ | 
| <a href="#rect_t_rect_cast">rect\_cast</a> | 转换为rect对象。 |
| <a href="#rect_t_rect_create">rect\_create</a> | 创建rect对象。 |
| <a href="#rect_t_rect_destroy">rect\_destroy</a> |  |
| <a href="#rect_t_rect_set">rect\_set</a> | 设置rect对象的xywh。 |
### 属性
<p id="rect_t_properties">

| 属性名称 | 类型 | 说明 | 
| -------- | ----- | ------------ | 
| <a href="#rect_t_h">h</a> | wh\_t | 高度。 |
| <a href="#rect_t_w">w</a> | wh\_t | 宽度。 |
| <a href="#rect_t_x">x</a> | xy\_t | x坐标。 |
| <a href="#rect_t_y">y</a> | xy\_t | y坐标。 |
#### rect\_cast 函数
-----------------------

* 函数功能：

> <p id="rect_t_rect_cast"> 转换为rect对象。

 > 供脚本语言使用。



* 函数原型：

```
rect_t* rect_cast (rect_t* rect);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | rect\_t* | rect对象。 |
| rect | rect\_t* | rect对象。 |
#### rect\_create 函数
-----------------------

* 函数功能：

> <p id="rect_t_rect_create"> 创建rect对象。

 > 主要供脚本语言使用。




* 函数原型：

```
rect_t* rect_create (xy_t x, xy_t y, wh_t w, wh_t h);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | rect\_t* | rect对象。 |
| x | xy\_t | x坐标。 |
| y | xy\_t | y坐标。 |
| w | wh\_t | 宽度。 |
| h | wh\_t | 高度。 |
#### rect\_destroy 函数
-----------------------

* 函数功能：

> <p id="rect_t_rect_destroy">
 销毁rect对象。
 > 主要供脚本语言使用。




* 函数原型：

```
ret_t rect_destroy (rect_t* r);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败。 |
| r | rect\_t* | rect对象。 |
#### rect\_set 函数
-----------------------

* 函数功能：

> <p id="rect_t_rect_set"> 设置rect对象的xywh。

 > 主要供脚本语言使用。




* 函数原型：

```
rect_t* rect_set (rect_t* rect, xy_t x, xy_t y, wh_t w, wh_t h);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | rect\_t* | rect对象。 |
| rect | rect\_t* | rect对象。 |
| x | xy\_t | x坐标。 |
| y | xy\_t | y坐标。 |
| w | wh\_t | 宽度。 |
| h | wh\_t | 高度。 |
#### h 属性
-----------------------
> <p id="rect_t_h"> 高度。


* 类型：wh\_t

| 特性 | 是否支持 |
| -------- | ----- |
| 可直接读取 | 是 |
| 可直接修改 | 否 |
| 可脚本化   | 是 |
#### w 属性
-----------------------
> <p id="rect_t_w"> 宽度。


* 类型：wh\_t

| 特性 | 是否支持 |
| -------- | ----- |
| 可直接读取 | 是 |
| 可直接修改 | 否 |
| 可脚本化   | 是 |
#### x 属性
-----------------------
> <p id="rect_t_x"> x坐标。


* 类型：xy\_t

| 特性 | 是否支持 |
| -------- | ----- |
| 可直接读取 | 是 |
| 可直接修改 | 否 |
| 可脚本化   | 是 |
#### y 属性
-----------------------
> <p id="rect_t_y"> y坐标。


* 类型：xy\_t

| 特性 | 是否支持 |
| -------- | ----- |
| 可直接读取 | 是 |
| 可直接修改 | 否 |
| 可脚本化   | 是 |
