#!/usr/bin/env python3
import os

FILES_EXT = (".c", ".cpp", ".h", ".hpp", ".py", ".sh", ".tex", ".md")

# 你想要的資料夾順序，越前面越優先
FOLDER_ORDER = ["DataStructure","Math","String","Graph","DP","Geometry","Tree","Misc"]
FOLDER_ORDER += ["AnotherVersion" + e for e in FOLDER_ORDER]

def insert_path(tree, parts, fullpath):
    """把路徑拆成多層，遞迴插入 list of dict"""
    if len(parts) == 1:
        tree.append({parts[0]: [fullpath]})
    else:
        for item in tree:
            if parts[0] in item:
                insert_path(item[parts[0]], parts[1:], fullpath)
                return
        new_branch = []
        tree.append({parts[0]: new_branch})
        insert_path(new_branch, parts[1:], fullpath)

def sort_tree(tree):
    """根據 FOLDER_ORDER 排序資料夾，其它資料夾按字母排序"""
    def folder_key(d):
        name = list(d.keys())[0]
        if name in FOLDER_ORDER:
            return FOLDER_ORDER.index(name)
        return len(FOLDER_ORDER) + ord(name[0])
    tree.sort(key=folder_key)
    for item in tree:
        name = list(item.keys())[0]
        sub = item[name]
        if isinstance(sub, list):
            # 遞迴排序子資料夾
            sub_dicts = [x for x in sub if isinstance(x, dict)]
            sort_tree(sub_dicts)
    return tree

def dump_yaml(tree, indent=4, level=1):
    """手動生成 YAML 字串"""
    lines = []
    spacer = " " * (indent * level)
    for item in tree:
        name = list(item.keys())[0]
        sub = item[name]
        lines.append(f"{spacer}- {name}:")
        if all(isinstance(x, str) for x in sub):
            # 底層檔案
            for f in sub:
                lines.append(f"{spacer}{' ' * indent}- {f}")
        else:
            # 子資料夾
            lines.extend(dump_yaml(sub, indent, level + 1))
    return lines

def main():
    root_dir = "nacl"
    tree = []

    for dirpath, _, files in os.walk(root_dir):
        for f in sorted(files):
            if f.endswith(FILES_EXT):
                fullpath = os.path.join(dirpath, f)
                relpath = os.path.relpath(fullpath, root_dir).replace(os.sep, "/")
                parts = relpath.split("/")
                insert_path(tree, parts, relpath)

    # 排序
    sort_tree(tree)

    # 輸出 YAML
    with open("codebook/config.yaml", "w", encoding="utf-8") as f:
        f.write("include:\n")
        for line in dump_yaml(tree):
            f.write(line + "\n")

if __name__ == "__main__":
    main()
