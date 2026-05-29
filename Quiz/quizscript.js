// --- CONFIG: map subjects to JSON file links ---
let subjectFiles = {};

async function loadSubjectManifest() {
  const response = await fetch("../Quizsubjects/subjects.json");

  if (!response.ok) {
    throw new Error("Failed to load subject manifest");
  }

  subjectFiles = await response.json();

  generateSubjectCheckboxes();
}

// --- DOM elements ---
const button = document.getElementById("startBtn");
const output = document.getElementById("output");
const message = document.getElementById("message");
const numInput = document.getElementById("numQuestions");
const quizContainer = document.getElementById("quiz-container");

// --- helper: load questions for one subject ---
function generateSubjectCheckboxes() {
  const container = document.getElementById("subject-list");
  container.innerHTML = "";

  Object.keys(subjectFiles).forEach(subject => {
    const label = document.createElement("label");

    const input = document.createElement("input");
    input.type = "checkbox";
    input.value = subject;

    label.appendChild(input);

    // Nicely formatted label text
    const text = document.createTextNode(
      " " + subject.charAt(0).toUpperCase() + subject.slice(1)
    );
    label.appendChild(text);

    container.appendChild(label);
    container.appendChild(document.createElement("br"));
  });
}


async function loadQuestions(subject) {
  const url = subjectFiles[subject];

  if (!url) {
    throw new Error(`No JSON file defined for subject: ${subject}`);
  }

  const response = await fetch(url);

  if (!response.ok) {
    throw new Error(`Failed to load questions for ${subject}`);
  }

  return response.json();
}

// --- helper: shuffle array (Fisher-Yates) ---
function shuffle(array) {
  const arr = [...array];
  for (let i = arr.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [arr[i], arr[j]] = [arr[j], arr[i]];
  }
  return arr;
}

// --- render quiz questions ---
function renderQuiz(questions) {
  quizContainer.innerHTML = "";

  questions.forEach((q, idx) => {
    const questionEl = document.createElement("div");
    questionEl.classList.add("question");

    // question text
    const title = document.createElement("p");
    title.textContent = `${idx + 1}. ${q.question}`;
    questionEl.appendChild(title);

    // Optional image
    if (q.image) {
      const img = document.createElement("img");
      img.src = q.image;
      img.alt = "Question illustration";
      img.style.maxWidth = "100%";
      img.style.margin = "10px 0";

  questionEl.appendChild(img);
}

    // multiple-choice
    if (q.type === "multiple-choice") {
      q.options.forEach((opt, i) => {
        const label = document.createElement("label");
        const input = document.createElement("input");

        input.type = "radio";
        input.name = `q${idx}`;
        input.value = i;

        label.appendChild(input);
        label.append(opt);
        questionEl.appendChild(label);
        questionEl.appendChild(document.createElement("br"));
      });
    }

    // number input
    if (q.type === "number") {
      const input = document.createElement("input");
      input.type = "number";
      input.name = `q${idx}`;
      questionEl.appendChild(input);
    }

    quizContainer.appendChild(questionEl);
  });

  // add submit button
  const submitBtn = document.createElement("button");
  submitBtn.textContent = "Submit";
  submitBtn.addEventListener("click", () => checkAnswers(questions));
  quizContainer.appendChild(submitBtn);

  // Score placeholder BELOW submit button
  const scoreDiv = document.createElement("div");
  scoreDiv.id = "scoreDiv";
  quizContainer.appendChild(scoreDiv);
}

// --- check answers and show score ---
function checkAnswers(questions) {
  let score = 0;

  questions.forEach((q, idx) => {
    const answerEls = document.getElementsByName(`q${idx}`);

    if (q.type === "multiple-choice") {
      const selected = Array.from(answerEls).find(el => el.checked);
      if (selected && Number(selected.value) === q.answer) {
        score++;
      }
    }

    if (q.type === "number") {
      const val = Number(answerEls[0].value);
      const tolerance = q.tolerance || 0;
      if (Math.abs(val - q.answer) <= tolerance) {
        score++;
      }
    }
  });

  const scoreDiv = document.getElementById("scoreDiv");
  scoreDiv.textContent = `Score: ${score} / ${questions.length}`;
}

// --- main button handler ---
button.addEventListener("click", async () => {
  message.textContent = "";
  output.textContent = "";
  quizContainer.innerHTML = "";

  const checkboxes = document.querySelectorAll(
    '#quiz-setup input[type="checkbox"]:checked'
  );

  const subjects = Array.from(checkboxes).map(cb => cb.value);
  const numQuestions = Number(numInput.value);

  // validation
  if (subjects.length === 0) {
    message.textContent = "Please select at least one subject.";
    return;
  }

  if (!Number.isInteger(numQuestions) || numQuestions < 1) {
    message.textContent = "Please enter a valid number of questions.";
    return;
  }

  try {
    const allQuestions = [];

    for (const subject of subjects) {
      const questions = await loadQuestions(subject);
      allQuestions.push(...questions);
    }

    const selected = shuffle(allQuestions).slice(0, numQuestions);

    renderQuiz(selected);

  } catch (error) {
    message.textContent = error.message;
  }
});

loadSubjectManifest().catch(err => {
  message.textContent = err.message;
});
