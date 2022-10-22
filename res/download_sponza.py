import os
import pathlib
import wget
import zipfile


script_parent_dir = pathlib.PurePath(os.path.realpath(__file__)).parent
sponza_dir = script_parent_dir / "sponza"
main_sponza_url = "https://cdrdv2.intel.com/v1/dl/getContent/726594"
main_sponza_dir = sponza_dir / "main_sponza"
main_sponza_zip_filename = "main_sponza.zip"
main_sponza_zip_path = sponza_dir / "main_sponza.zip"


def main():
    if not os.path.exists(sponza_dir):
        print(f"Creating directory {sponza_dir}")
        os.makedirs(sponza_dir)

    if not os.path.exists(main_sponza_dir):
        if not os.path.exists(main_sponza_zip_path):
            print(f"Downloading {main_sponza_zip_filename}")
            wget.download(main_sponza_url, str(main_sponza_zip_path))
        else:
            print(f"{main_sponza_zip_filename} found in local cache")

        print(f"Extracting {main_sponza_zip_filename}... ", end="", flush=True)
        with zipfile.ZipFile(main_sponza_zip_path, "r") as zip_ref:
            zip_ref.extractall(main_sponza_dir)
        print("done")


if __name__ == "__main__":
    main()
