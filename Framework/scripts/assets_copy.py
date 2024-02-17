import shutil
import os


def delete_folder(folder_path):
    if os.path.exists(folder_path):
        shutil.rmtree(folder_path)


def copy_folder(src_path, dst_path):
    # os.makedirs(dst_path, exist_ok=True)
    shutil.copytree(src_path, dst_path)


if __name__ == '__main__':

    src_path = '../assets/'
    dst_debug_path = '../../Artifacts/Debug/assets/'
    dst_release_path = '../../Artifacts/Release/assets/'

    delete_folder(dst_debug_path)
    delete_folder(dst_release_path)

    copy_folder(src_path, dst_debug_path)
    copy_folder(src_path, dst_release_path)