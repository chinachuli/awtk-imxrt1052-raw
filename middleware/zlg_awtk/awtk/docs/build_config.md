# 特殊平台编译配置

有些平台编译比较特殊，不能使用 scons 编译，也不能使用 keil 编译。我们用一个配置文件描述项目，然后用脚本来编译或生成项目模板。目前有 web 版本和 android 版本使用这种方式。

配置文件采用 JSON 格式。

## 一、通用选项

* name 应用程序名称（不支持中文和特殊符号）。
* version 版本号。
* assets 资源所在的目录（相对于配置文件所在的目录）。
* sources 源文件列表（相对于配置文件所在的目录）。文件名支持通配符如*.c。

> sources 虽然是通用选项，但是不同平台，包含的源文件可能并不相同，此时应该放到具体平台之下。

## 二、web 平台选项

web 平台选项放在 web 子键下面，目前支持以下选项：

* app_type 目前可选择的值有。"c"表示用 C 语言开发的应用程序，"js"表示用 Javascript 开发的应用程序。
* config 用于指定一些运行参数。
  * width 如果应用开发时没有做自适应性布局，可以用 width 参数指定画布的宽度。
  * height 如果应用开发时没有做自适应性布局，可以用 height 参数指定画布的高度。
  * defaultFont 缺省字体。缺省为"sans"。
  * fontScale 字体的缩放比例。缺省为 1。

> config 中的参数也可以直接在 URL 中指定。如：

```
http://192.168.1.117:8080/demoui/index.html?width=480&height=800&fontScale=0.8&defaultFont=serif
```

如：

用 C 语言写的 demoui 的配置文件：

```
  "web": {
    "app_type":"c",
    "sources":["demo_ui_app.c"],
    "config" : { 
      "fontScale":"0.8",
      "defaultFont":"sans"
    }   
  }, 
```

用 Javascript 写的 demoui 的配置文件：

```
  "web": {
    "app_type":"js",
    "sources":["demoui.js"],
    "config" : { 
      "fontScale":"0.8",
      "defaultFont":"sans"
    }   
  }, 
```

## 三、android 平台选项

android 平台选项放在 android 子键下面，目前支持以下选项：

* app_name 应用程序的完整名称。如：org.zlgopen.demoui

示例：

```
  "android" : { 
    "app_name":"org.zlgopen.demoui",
    "sources":["assets.c",  "assets.h", "demo_main.c", "demo_ui_app.c", "vg_common.inc"]
  }
```

## 四、完整示例

下面是 demoui 的完整示例

```
{
  "name":"demoui",
  "version":"1.0",
  "assets" : "assets",
  "web": {
    "app_type":"c",
    "sources":["demo_ui_app.c"],
    "config" : { 
      "fontScale":"0.8",
      "defaultFont":"sans"
    }   
  },  
  "android" : { 
    "app_name":"org.zlgopen.demoui",
    "sources":["assets.c",  "assets.h", "demo_main.c", "demo_ui_app.c", "vg_common.inc"]
  }
}
```
