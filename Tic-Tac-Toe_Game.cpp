import tkinter as tk
from tkinter import messagebox

# Set up the main window
root = tk.Tk()
root.title("Tic-Tac-Toe")
root.geometry("400x400")  # Set the window size to 400x400 pixels

# Initialize variables
current_player = "X"
buttons = [[None for _ in range(3)] for _ in range(3)]

# Function to check for a win or draw
def check_winner():
    # Check rows, columns, and diagonals
    for i in range(3):
        if buttons[i][0]["text"] == buttons[i][1]["text"] == buttons[i][2]["text"] != "":
            return buttons[i][0]["text"], [(i, 0), (i, 1), (i, 2)]
        if buttons[0][i]["text"] == buttons[1][i]["text"] == buttons[2][i]["text"] != "":
            return buttons[0][i]["text"], [(0, i), (1, i), (2, i)]

    if buttons[0][0]["text"] == buttons[1][1]["text"] == buttons[2][2]["text"] != "":
        return buttons[0][0]["text"], [(0, 0), (1, 1), (2, 2)]
    if buttons[0][2]["text"] == buttons[1][1]["text"] == buttons[2][0]["text"] != "":
        return buttons[0][2]["text"], [(0, 2), (1, 1), (2, 0)]

    # Check for a draw
    if all(buttons[i][j]["text"] != "" for i in range(3) for j in range(3)):
        return "Draw", []
    return None, []

# Function to handle button clicks
def on_button_click(row, col):
    global current_player
    if buttons[row][col]["text"] == "":
        buttons[row][col]["text"] = current_player
        if current_player == "X":
            buttons[row][col]["bg"] = "#A9A9A9"  # Gray background for "X"
            buttons[row][col]["fg"] = "#FFFFFF"  # White text
        else:
            buttons[row][col]["bg"] = "#FFFFFF"  # White background for "O"
            buttons[row][col]["fg"] = "#A9A9A9"  # Gray text
        buttons[row][col].config(state="disabled")  # Disable the button after click
        winner, winning_combo = check_winner()
        if winner:
            if winner == "Draw":
                messagebox.showinfo("Tic-Tac-Toe", "It's a Draw!")
            else:
                highlight_winner(winning_combo)
                root.after(1000, lambda: messagebox.showinfo("Tic-Tac-Toe", f"Player {winner} wins!"))
            root.after(1500, reset_game)
        else:
            current_player = "O" if current_player == "X" else "X"

# Function to highlight the winning combination
def highlight_winner(combo):
    for (row, col) in combo:
        buttons[row][col]["bg"] = "#D3D3D3"  # Light gray background for winning combination

# Function to reset the game
def reset_game():
    global current_player
    current_player = "X"
    for i in range(3):
        for j in range(3):
            buttons[i][j]["text"] = ""
            buttons[i][j]["bg"] = "SystemButtonFace"  # Reset to default button color
            buttons[i][j].config(state="normal")  # Re-enable all buttons

# Create the grid of buttons
for i in range(3):
    for j in range(3):
        buttons[i][j] = tk.Button(root, text="", font=("Arial", 24), width=5, height=2,
                                  command=lambda i=i, j=j: on_button_click(i, j))
        buttons[i][j].grid(row=i, column=j, sticky="nsew")  # Make buttons expand to fill grid cells

# Configure row and column weights to make buttons resize with the window
for i in range(3):
    root.grid_rowconfigure(i, weight=1)
    root.grid_columnconfigure(i, weight=1)

# Start the Tkinter event loop
root.mainloop()
