## 抓取网页，生成输入法联想词库。

### 生成数据

在当前目录下运行：

```
npm install
node gen.js
```

### 更新数据

在awtk目录下运行：

```
./bin/resgen tools/word_gen/words.bin src/input_methods/suggest_words.inc 
```

### 注意：
node\_modules/segment/lib/module/DictTokenizer.js#getChunks 可能导致OOM。

如果遇到问题，可以限制chunks.length的大小，如下面限制为5000。

```
let getChunksCallsNr = 0;
var getChunks = function (wordpos, pos, text) {
  var words = wordpos[pos] || [];
  // debug('getChunks: ');
  // debug(words);
  // throw new Error();
  var ret = [];
  if(getChunksCallsNr > 150) {
    throw "get Chunks error";
  }
  
  getChunksCallsNr++;
  for (var i = 0; i < words.length; i++) {
    var word = words[i];
    //debug(word);
    var nextcur = word.c + word.w.length;
    if (!wordpos[nextcur]) {
      ret.push([word]);
    } else  {
      var chunks = getChunks(wordpos, nextcur);
      for (var j = 0; j < chunks.length && j < 5000; j++) {
        ret.push([word].concat(chunks[j]));
      }
    }
  }
  getChunksCallsNr--;

  return ret;
};
```

