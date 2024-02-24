import shutil
import os


def delete_folder(folder_path):
    if os.path.exists(folder_path):
        shutil.rmtree(folder_path)


def copy_folder(src_path, dst_path):
    # os.makedirs(dst_path, exist_ok=True)
    shutil.copytree(src_path, dst_path)


if __name__ == '__main__':

    src_path = '../config/'
    dst_path = '../artifacts/config/'

    delete_folder(dst_path)
    copy_folder(src_path, dst_path)
