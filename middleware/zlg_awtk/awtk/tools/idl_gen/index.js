const fs = require('fs');
const path = require('path');
const glob = require('glob')

class IDLGenerator {
  parseDesc(str) {
    if (str.indexOf('/**') < 0 && str.indexOf('*/') < 0) {
      let desc = str;
      let start = desc.indexOf('*');

      if (start >= 0) {
        desc = desc.substr(start + 1);
      }

      return desc + '\n';
    } else {
      return '';
    }
  }

  parseAnnotation(str) {
    let annotation = {};
    let value = str.substr(str.indexOf('['));
    let arr = JSON.parse(value);

    arr.forEach(iter => {
      const d = iter.indexOf(':');
      if (d >= 0) {
        const k = iter.substr(0, d);
        const v = iter.substr(d + 1);
        annotation[k] = v;
      } else {
        annotation[iter] = true;
      }
    })

    return annotation;
  }

  getValue(str) {
    const s = str.substr(str.indexOf('@') + 1)
    const v = s.substr(s.indexOf(' '));

    return v.trim();
  }

  parseName(str) {
    return this.getValue(str);
  }
  
  parseAlias(str) {
    return this.getValue(str);
  }

  parsePrefix(str) {
    return this.getValue(str);
  }

  parseParent(str) {
    return this.getValue(str);
  }

  parseParam(str) {
    const param = {};
    const type = this.parseType(str);
    const nameDesc = str.substr(str.indexOf('}') + 1).trim();
    const d = nameDesc.indexOf(' ');
    const name = nameDesc.substr(0, d).trim();
    const desc = nameDesc.substr(d).trim();

    param.type = type;
    param.name = name;
    param.desc = desc;

    return param;
  }

  parseTypeAndName(str) {
    const typeAndName = {};
    const type = this.parseType(str);
    const name = str.substr(str.indexOf('}') + 1).trim();

    typeAndName.type = type.trim();
    typeAndName.name = name.trim();

    return typeAndName;
  }

  parseType(str) {
    const start = str.indexOf('{');
    const end = str.indexOf('}');
    const type = str.substr(start + 1, end - start - 1);

    return type;
  }

  parseReturn(str) {
    const ret = {};
    const type = this.parseType(str);
    const desc = str.substr(str.indexOf('}') + 1);

    ret.type = type.trim();
    ret.desc = desc.trim();

    return ret;
  }

  parseMethod(comment) {
    const method = {
      params: [],
      annotation: {},
      desc: '',
      name: ''
    };

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@method') >= 0) {
        method.name = this.parseName(iter);
      }else if (iter.indexOf('@alias') >= 0) {
        method.alias = this.parseAlias(iter);
      } else if (iter.indexOf(' @annotation') >= 0) {
        method.annotation = this.parseAnnotation(iter);
      } else if (iter.indexOf(' @param') >= 0) {
        method.params.push(this.parseParam(iter));
      } else if (iter.indexOf(' @return') >= 0) {
        method.return = this.parseReturn(iter);
      } else {
        method.desc += this.parseDesc(iter);
      }
    });

    if (method.annotation.global) {
      method.type = 'method';
      method.header = this.filename;

      this.result.push(method);
    } else if (this.cls) {
      this.cls.methods.push(method);
    }

    return;
  }

  parseProperty(comment) {
    const property = {
      name: '',
      desc: ''
    };

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@property') >= 0) {
        const typeAndName = this.parseTypeAndName(iter);
        property.type = typeAndName.type;
        property.name = typeAndName.name;
      } else if (iter.indexOf('@annotation') >= 0) {
        property.annotation = this.parseAnnotation(iter);
      } else {
        property.desc += this.parseDesc(iter);
      }
    });

    if(this.cls) {
      this.cls.properties.push(property);
    }

    return;
  }
  
  parseEvent(comment) {
    const event = {
      name: '',
      desc: ''
    };

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@event') >= 0) {
        const typeAndName = this.parseTypeAndName(iter);
        event.type = typeAndName.type;
        event.name = typeAndName.name;
      } else if (iter.indexOf('@annotation') >= 0) {
        event.annotation = this.parseAnnotation(iter);
      } else {
        event.desc += this.parseDesc(iter);
      }
    });

    if(this.cls) {
      this.cls.events.push(event);
    }

    return;
  }

  parseClass(comment) {
    let cls = {};
    cls.type = 'class';
    cls.methods = [];
    cls.events = [];
    cls.properties = [];
    cls.header = this.filename;
    cls.desc = '';

    this.cls = cls;

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@class') >= 0) {
        cls.name = this.parseName(iter);
      } else if (iter.indexOf('@annotation') >= 0) {
        cls.annotation = this.parseAnnotation(iter);
      }else if (iter.indexOf('@alias') >= 0) {
        cls.alias = this.parseAlias(iter);
      } else if (iter.indexOf('@parent') >= 0) {
        cls.parent = this.parseParent(iter);
      } else {
        cls.desc += this.parseDesc(iter);
      }
    });

    this.result.push(cls);
  }

  parseEnum(comment) {
    let cls = {};
    cls.type = 'enum';
    cls.desc = '';
    cls.consts = [];
    cls.header = this.filename;

    this.cls = cls;

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@enum') >= 0) {
        cls.name = this.parseName(iter);
        cls.prefix = cls.name.replace(/t$/, "").toUpperCase();
      } else if (iter.indexOf('@annotation') >= 0) {
        cls.annotation = this.parseAnnotation(iter);
      } else if (iter.indexOf('@prefix') >= 0) {
        cls.prefix = this.parsePrefix(iter);
      } else {
        cls.desc += this.parseDesc(iter);
      }
    });

    this.result.push(cls);
  }

  parseConst(comment) {
    let c = {};
    c.desc = '';

    comment.split('\n').forEach(iter => {
      if (iter.indexOf('@const') >= 0) {
        c.name = this.parseName(iter);
      } else {
        c.desc += this.parseDesc(iter);
      }
    });

    if (this.cls) {
      this.cls.consts.push(c);
    }
  }

  parseFileContent(filename, content) {
    let start = 0;
    let end = 0;
    let str = content;

    do {
      start = str.indexOf('/**');
      if (start >= 0) {
        str = str.substr(start);
        end = str.indexOf('*/');
        if (end >= 0) {
          const comment = str.substr(0, end + 3);
          if (comment.indexOf('* @') >= 0) {
            if (comment.indexOf(' @class') >= 0) {
              this.parseClass(comment);
            } else if (comment.indexOf(' @method') >= 0) {
              this.parseMethod(comment);
            } else if (comment.indexOf(' @property') >= 0) {
              this.parseProperty(comment);
            } else if (comment.indexOf(' @event') >= 0) {
              this.parseEvent(comment);
            } else if (comment.indexOf(' @const') >= 0) {
              this.parseConst(comment);
            } else if (comment.indexOf(' @enum') >= 0) {
              this.parseEnum(comment);
            }
          }

          str = str.substr(end + 3);
        }
      }

    } while (start >= 0 && end >= 0)

    return;
  }

  parseFile(filename) {
    const content = fs.readFileSync(filename).toString();
    const name = filename.match(/[a-z|_\d|\.|A-Z]*\/[a-z|_\d|\.|A-Z]*$/)[0];

    console.log('Process: ' + filename);
    this.filename = name;
    this.fullFileName = filename;
    this.parseFileContent(name, content);
  }

  parseFolder(folder) {
    const files = glob.sync(folder);
    for (let i = 0; i < files.length; i++) {
      const iter = files[i];
      this.parseFile(iter);
    }

    return;
  }

  updateLevel() {
    let json = this.result;

    function getClass(name) {
      return json.find(iter => {
        return iter.name === name;
      });
    }

    function updateLevel(cls) {
      if(cls.level) {
        return cls.level;
      }
  
      cls.level = 1;
      if(cls.parent) {
        let parent = getClass(cls.parent);
        if(parent) {
          cls.level += updateLevel(parent);
        } else {
          cls.level += 1;
          console.log('Warnning: not found class ' + cls.parent);
        }
      }

      return cls.level;
    }

    json.forEach(iter => {
      updateLevel(iter);
    });
  }
  
  sort() {
    this.result.sort((a, b) => {
      return a.level - b.level;
    });
  }

  postProcess() {
    this.updateLevel();
    this.sort();
  }

  saveResult(filename) {
    const str = JSON.stringify(this.result, null, '  ');
    fs.writeFileSync(filename, str);
  }

  static gen(sourcesPath, outputIDL) {
    let gen = new IDLGenerator();
    
    gen.result = []
    gen.parseFolder(sourcesPath + '/**/*.h');

    gen.postProcess();
    gen.saveResult(outputIDL);
    console.log('\n==============================================');
    console.log(`${sourcesPath} ==> ${outputIDL}`);
    console.log('==============================================');
  }
}

let outputIDL = 'idl.json';
let sourcesPath = path.normalize(path.join(__dirname, '../../src'));

if(process.argv.length == 3) {
  outputIDL = process.argv[2];
} else if(process.argv.length > 3) {
  outputIDL = process.argv[2];
  sourcesPath = path.normalize(process.argv[3]);
}

if(sourcesPath === '-h' || sourcesPath === '--help') {
  console.log('Usage: node index.js outputIDL sourcesPath');
  process.exit(0);
}

IDLGenerator.gen(sourcesPath, outputIDL)
