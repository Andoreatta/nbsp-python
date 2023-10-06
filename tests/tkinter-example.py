import tkinter as tk
from tkinter import messagebox
import tkinter.ttk as ttk
import nbsp_python as nbsp

window = tk.Tk()
window.title("NBioBSP Python Example")
window.geometry("380x350")

handle = nbsp.initialize_handle()

def open_nbsp_device():
    nbsp.open_device()
    result_label.config(text="Device opened successfully." if nbsp.is_device_open() else "Failed to open device.")

def close_nbsp_device():
    nbsp.close_device()
    result_label.config(text="Device closed successfully." if not nbsp.is_device_open() else "Failed to close device.")


def capture_fingerprint():
    global fingerprint_hash
    if not nbsp.is_device_open():
        result_label.config(text="Please open the device first.")
        return
    if not user_id_entry.get():
        result_label.config(text="Please enter a user ID.")
        return

    handle = nbsp.capture(selected_option.get(), 5000)
    fingerprint_hash = nbsp.extract_fir_text(handle)
    messagebox.showinfo("Fingerprint Hash", fingerprint_hash)
    verify_button.config(state="normal")
    messagebox.showinfo("Capture Successful", "You can now press VERIFY to verify the fingerprint against the one you just captured.")


def verify_fingerprint():
    try:
        nbsp.verify(handle)
        result_label.config(text="Valid fingerprint!")
    except RuntimeError as e:
        result_label.config(text="Error: " + str(e))


def init_index_search():
    nbsp.init_index_search()
    add_fir_button.config(state="normal")
    result_label.config(text="Indexsearch initialized successfully.")

# has errors
# def add_fingerprint_to_indexsearch():
#     nbsp.add_fir_to_index_search(fingerprint_hash, int(user_id_entry.get()))
#     result_label.config(text="Last capture added to indexsearch successfully.")

# --- GUI --- #

open_device_button = ttk.Button(window, text="OPEN DEVICE", command=open_nbsp_device)
open_device_button.grid(row=0, column=0, padx=10, pady=10)

close_device_button = ttk.Button(window, text="CLOSE DEVICE", command=close_nbsp_device)
close_device_button.grid(row=0, column=1, padx=10, pady=10)

ttk.Separator(window, orient="horizontal").grid(row=1, column=0, columnspan=2, sticky="ew", padx=10, pady=10)

capture_button = ttk.Button(window, text="CAPTURE", command=capture_fingerprint)
capture_button.grid(row=2, column=0, padx=10, pady=10)

options = ["enroll", "verify", "enroll_for_verification", "enroll_for_identification"]
selected_option = tk.StringVar(value=options[0])
ttk.OptionMenu(window, selected_option, *options).grid(row=2, column=1, padx=10, pady=10)

ttk.Label(window, text="User ID:").grid(row=3, column=0, padx=10, pady=10)
user_id_entry = ttk.Entry(window)
user_id_entry.grid(row=3, column=1, padx=10, pady=10)

ttk.Separator(window, orient="horizontal").grid(row=5, column=0, columnspan=2, sticky="ew", padx=10, pady=10)

verify_button = ttk.Button(window, text="VERIFY AGAINST CAPTURE", state="disabled", command=verify_fingerprint)
verify_button.grid(row=4, column=0, padx=10, pady=10)

init_button = ttk.Button(window, text="INITIALIZE INDEXSEARCH", command=init_index_search)
init_button.grid(row=6, column=0, padx=10, pady=10)

add_fir_button = ttk.Button(window, text="ADD LAST CAPTURE TO INDEXSEARCH", state="disabled", command=add_fingerprint_to_indexsearch)
add_fir_button.grid(row=7, column=0, padx=10, pady=10)

result_label = ttk.Label(window, text="")
result_label.grid(row=8, column=0, columnspan=2, padx=10, pady=10)

window.mainloop()