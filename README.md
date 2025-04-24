# Friend-Recommendation-Engine

A simple command-line friend recommendation system implemented in C++. This system models social connections and provides friend suggestions based on mutual friendships.


## 📌 Key Features

- Add users and friendships to a graph-based network
- Represent and manage user interests
- Recommend top-N potential friends based on:
  - Mutual friend count
  - Shared interest categories
- Score-based recommendation ranking

## 🧠 How It Works

The system scores potential recommendations using the formula:
Score = (Mutual Friends × 10) + Shared Interests

## ▶️ Run
./main.exe

## Sample Output
![image](https://github.com/user-attachments/assets/522b980e-e28b-4571-a459-7b817dd49078)
![image](https://github.com/user-attachments/assets/f3322e1f-ea6e-4d20-add2-1e7d8fbbe060)
![image](https://github.com/user-attachments/assets/4efe3a20-9a9b-4b6a-916c-66ac8dfff51c)

## UML Diagram 
![image](https://github.com/user-attachments/assets/56e7590c-a21d-4df1-ba88-5b55f0a28bab)

## Sequence Diagram 
![image](https://github.com/user-attachments/assets/6b8411a8-8060-45bb-9d41-064a5deedd64)


## 📌 Future Enhancements
Read/write users and friendships from a file or database

Graph visualization (e.g., Graphviz or Qt)

Command-line menu interface

Unit testing support

