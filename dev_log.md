# 📓 Development Log — Algorithm Visualizer in C++

Welcome to the ongoing development log of my project: a C++ SFML-based algorithm visualizer to learn, explore, and teach algorithms visually and intuitively.

---

## 🔗 Useful Links

- 📁 [C++ reference](https://en.cppreference.com/index.html)
- 📁 [SFML Docs](https://www.sfml-dev.org/documentation/)
- 📘 [Introduction to Algorithms book](https://enos.itcollege.ee/~japoia/algorithms/GT/Introduction_to_algorithms-3rd%20Edition.pdf)


---
## 🗓️ Week 1, 01–07.08.2025

### ✔️ What I Did
- [x] Identified project structure
- [x] Set up Git & SFML
- [x] Created main window loop
- [x] Built algorithm visualizer engine
- [x] Designed abstract algorithm class

### 📚 What I Learned
- High-level overview of project creation
- Basics of SFML
- Virtual functions and abstract classes

### ❗️Challenges & Struggles
- Coming from a C background, I'm not as comfortable with OOP as I’d like to be. I had to read a lot about the object-oriented paradigm. The most challenging part was understanding polymorphism, virtual functions, and abstract classes.
- GUI or CUI?

### 🔜 What’s Next
- [ ] Create the main function with a text-based interface
- [ ] Implement the core logic for interacting with the program
- [ ] Add the first algorithm (Bubble Sort)


### 🖋 Notes
  After trying to implement the visualizer with a GUI, I found it a bit tedious — building all the welcome, main, and visualization windows felt like too much. I have to admit that, for now, it’s either beyond my current skill level or, more likely, beyond my current dedication. I just don’t want to spend a week or two creating a full graphical user interface. And a poorly designed welcome screen isn’t something I’d be happy with either.
So, if I can’t do it well, I’d rather try something else — in this case, a CUI (Console User Interface). It’ll be much easier to build and interact with, and I can spend far less time on that part while focusing on the actual goal: implementing algorithm visualization. That’s the whole point of this project — to learn more about algorithms.
Later, I might add a proper GUI on top of the core CUI logic once the foundation is solid.

  Was this week unproductive? Maybe. But at least I built a bare-bones version of the project (actually two versions!) and learned **a lot** about C++ — especially classes, virtual functions, and abstract classes. I also worked quite a bit with SFML, although I fell into the “AI trap”: it provided me a lot of copy-pasteable code, so I didn’t learn as much as I could have.
I’ve decided to reduce AI usage to a bare minimum: no more copy-pasting code, not even if I ask. Hints only! Otherwise, I get lazy — and the AI sometimes hallucinates anyway.

  Anyway, to avoid going off track — let’s just say this was more of a *setup & figure-it-out* week. I got a general understanding and idea of what the project will look like, so I’m not stopping here. I’m writing this on Day 6, with one day left. I probably won’t get much more done.

---

## 🗓️ Week 2, 08–14.08.2025

### ✔️ What I Did
- [ ] User text interface
- [ ] Input handling
- [ ] Main program logic and behavior
- [ ] BubbleSort visualization

### 📚 What I Learned
- More on inheritance
- Program logic
- A little more SFML
- I’m pretty sure that after implementing the BubbleSort visualization, I have it “on the tip of my toes”

### ❗️Challenges & Struggles
- I spent a lot of time thinking about how to store algorithms and initialize them after user input. For now, I think I’ve come up with a good solution.
- Some problems occurred with handling input (described in the notes).
- I still have issues with resizing the window — I need to do something about it.

### 🔜 What’s Next
- [ ] Heapsort?
- [ ] Properly handle window resizing
- [ ] Review user interaction in case of bugs or potential improvements
- [ ] Quicksort?

### 🖋 Notes
I’ve implemented a program structure that I’m quite happy with for now. To make the program fully modular, I just need to refine input handling. I’m considering implementing a friend class to manage global controls, such as:

- **Space** – stop/play
- **Arrow keys** – step-by-step visualization
- **R** – reset
- **F / S** – faster / slower
- **Q** – quit

Once I have this global input handling in place, I’ll only need to work on specific algorithm visualizations. After that, adding them to the `algomap` hashmap will be straightforward.

I also considered implementing input methods directly in the main visualizer class, but currently, I only have a pointer to the exact algorithm in the category visualizer class. I designed it this way in case I create a GUI version, as category segregation might make that easier. However, this means I’d need to paste the same input-handling logic into all category classes. Maybe that’s even better — for example, in the Graphs category, I might add more specific controls.

Long story short: for now, I think the program is in a good state (at least for a first project). The main current issue (aside from the low-quality visuals) is handling window resizing. I should address and fix this behavior.

For next week, I’ll focus on polishing user interaction logic, reviewing the overall program structure, and — if I have time — implementing another algorithm. Thankfully, it’s much easier now: I just need to write the main algorithm visualizer logic, paste the declaration in `.hpp` and the definition in `.cpp`, add the algorithm to the hashmap, and that’s it.

Oh, and I also need to rewrite the help file and update it with more information — just remembered!

---

I'm going to take a break from this project until September 14, probably. I need to prepare for exams, and this month I have more hours at my part-time job, so I'll be concentrating on the C language and, mainly, on memory handling.

---

