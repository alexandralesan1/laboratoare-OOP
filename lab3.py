import os
from datetime import datetime

MONITORED_DIR = "test_folder"


def get_file_info(path: str):
    stat = os.stat(path)
    creation_time = datetime.fromtimestamp(stat.st_ctime)
    last_modified_time = datetime.fromtimestamp(stat.st_mtime)
    name = os.path.basename(path)
    base, ext = os.path.splitext(name)
    return {
        "name": name,
        "ext": ext.lower(),
        "creation_time": creation_time,
        "last_modified_time": last_modified_time
    }


class MonitoredFile:
    def __init__(self, path: str):
        self.path = path
        self.info = get_file_info(path)

    def display_info(self):
        # Info generale
        print(f"Nume fișier: {self.info['name']}")
        print(f"Extensie: {self.info['ext']}")
        print(f"Data creării: {self.info['creation_time']}")
        print(f"Ultima modificare: {self.info['last_modified_time']}")

    def has_changed_since(self, previous_info):
        return previous_info['last_modified_time'] != self.info['last_modified_time']


class ImageFile(MonitoredFile):
    def display_info(self):
        super().display_info()
        # Simulare dimensiuni imagine
        width = 800
        height = 600
        print(f"Dimensiuni imagine: {width}x{height}")


class TextFile(MonitoredFile):
    def display_info(self):
        super().display_info()
        with open(self.path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        lines = content.split('\n')
        words = content.split()
        chars = len(content)
        print(f"Număr linii: {len(lines)}")
        print(f"Număr cuvinte: {len(words)}")
        print(f"Număr caractere: {chars}")


class ProgramFile(MonitoredFile):
    def display_info(self):
        super().display_info()
        with open(self.path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        class_count = sum(1 for l in lines if 'class ' in l)
        method_count = sum(1 for l in lines if 'def ' in l or 'void ' in l)
        print(f"Număr linii: {len(lines)}")
        print(f"Număr clase: {class_count}")
        print(f"Număr metode: {method_count}")


def create_monitored_file(path: str):
    info = get_file_info(path)
    ext = info['ext']
    if ext in ['.png', '.jpg']:
        return ImageFile(path)
    elif ext == '.txt':
        return TextFile(path)
    elif ext in ['.py', '.java']:
        return ProgramFile(path)
    else:
        return MonitoredFile(path)


class FolderMonitor:
    def __init__(self, directory: str):
        self.directory = directory
        self.snapshot_time = datetime.now()
        self.snapshot_files = {}
        self.current_files = {}
        self.update_current_files()
        self.take_snapshot()  # inițial

    def update_current_files(self):
        self.current_files = {}
        if not os.path.exists(self.directory):
            return
        for f in os.listdir(self.directory):
            path = os.path.join(self.directory, f)
            if os.path.isfile(path):
                mf = create_monitored_file(path)
                self.current_files[mf.info['name']] = mf

    def take_snapshot(self):
        self.snapshot_time = datetime.now()
        self.snapshot_files = {}
        for fname, mf in self.current_files.items():
            self.snapshot_files[fname] = mf.info.copy()

    def get_status(self):
        # Actualizează fișiere curente înainte de a obține status
        self.update_current_files()
        status_list = []
        # Fișiere șterse
        for fname in self.snapshot_files:
            if fname not in self.current_files:
                status_list.append((fname, "deleted"))
        # Fișiere noi sau modificate
        for fname, mf in self.current_files.items():
            if fname not in self.snapshot_files:
                status_list.append((fname, "new"))
            else:
                old_info = self.snapshot_files[fname]
                if mf.has_changed_since(old_info):
                    status_list.append((fname, "modified"))
                else:
                    status_list.append((fname, "unchanged"))
        return status_list

    def display_info(self, filename: str):
        # Actualizează lista de fișiere înainte de afișare info
        self.update_current_files()
        if filename in self.current_files:
            self.current_files[filename].display_info()
        else:
            print(f"Fișierul {filename} nu există în directorul curent.")

    def commit_changes(self):
        # Actualizează fișiere curente și face snapshot
        self.update_current_files()
        self.take_snapshot()
        print("Snapshot actualizat. Starea resetată la 'clean'.")


if __name__ == "__main__":
    # Creăm directorul dacă nu există
    if not os.path.exists(MONITORED_DIR):
        os.makedirs(MONITORED_DIR)

    monitor = FolderMonitor(MONITORED_DIR)

    print("Sistem monitorizare pornit (Nivel 9).")
    print("Comenzi disponibile: commit, status, info <fisier>, exit")

    while True:
        try:
            cmd = input("> ").strip()
        except EOFError:
            break

        if cmd == "exit":
            break

        if cmd == "commit":
            monitor.commit_changes()

        elif cmd.startswith("info"):
            parts = cmd.split()
            if len(parts) == 2:
                monitor.display_info(parts[1])
            else:
                print("Utilizare: info <nume_fisier>")

        elif cmd == "status":
            st = monitor.get_status()
            for fname, stat in st:
                if stat == "new":
                    print(f"{fname} este un fișier nou de la ultimul snapshot.")
                elif stat == "deleted":
                    print(f"{fname} a fost șters de la ultimul snapshot.")
                elif stat == "modified":
                    print(f"{fname} a fost modificat de la ultimul snapshot.")
                else:
                    print(f"{fname} este neschimbat.")
        else:
            print("Comandă necunoscută. Comenzi: commit, status, info <fisier>, exit")
