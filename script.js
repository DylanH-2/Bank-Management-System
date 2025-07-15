let accounts = [];

function createAccount() {
  const name = document.getElementById("accountName").value.trim();
  const balanceStr = document.getElementById("initialBalance").value.trim();
  const pin = document.getElementById("pin").value.trim();

  if (!/^[A-Za-z]+$/.test(name)) {
    alert("Name must contain only letters.");
    return;
  }

  if (!/^\d+(\.\d+)?$/.test(balanceStr)) {
    alert("Balance must be a number.");
    return;
  }

  if (!/^\d{4}$/.test(pin)) {
    alert("PIN must be exactly 4 digits.");
    return;
  }

  const account = {
    accountNum: Math.floor(1000 + Math.random() * 9000),
    name,
    balance: parseFloat(balanceStr),
    pin,
    transactions: [
      { type: "Initial deposit", amount: parseFloat(balanceStr) }
    ]
  };

  accounts.push(account);
  clearInputs();
  showAccounts();
}

function clearInputs() {
  document.getElementById("accountName").value = "";
  document.getElementById("initialBalance").value = "";
  document.getElementById("pin").value = "";
}

function showAccounts() {
  const div = document.getElementById("accountsList");
  if (accounts.length === 0) {
    div.innerHTML = "<p>No accounts to show.</p>";
    return;
  }

  let html = "";
  for (let acc of accounts) {
    html += `<div class="account">
      <p><strong>Account #${acc.accountNum}</strong> - ${acc.name} - $${acc.balance.toFixed(2)}</p>
      <button onclick="editAccount(${acc.accountNum})">Edit</button>
      <button onclick="withdrawOrDeposit(${acc.accountNum})">Withdraw/Deposit</button>
      <button onclick="showTransactions(${acc.accountNum})">Transactions</button>
      <button onclick="deleteAccount(${acc.accountNum})">Delete</button>
    </div>`;
  }
  div.innerHTML = html;
}

function findAccount(accountNum) {
  return accounts.find(acc => acc.accountNum === accountNum);
}

function editAccount(accountNum) {
  const acc = findAccount(accountNum);
  if (!acc) return;

  const pinTry = prompt("Enter PIN:");
  if (pinTry !== acc.pin) {
    alert("Wrong PIN.");
    return;
  }

  const option = prompt("1: Change name\n2: Change PIN\n3: Reset balance\n0: Cancel");
  if (option === "1") {
    let newName;
    do {
      newName = prompt("Enter new name (letters only):");
    } while (!/^[A-Za-z]+$/.test(newName));
    acc.name = newName;
  } else if (option === "2") {
    let newPin;
    do {
      newPin = prompt("Enter new 4-digit PIN:");
    } while (!/^\d{4}$/.test(newPin));
    acc.pin = newPin;
  } else if (option === "3") {
    acc.balance = 0;
    acc.transactions.push({ type: "reset balance", amount: 0 });
  }
  showAccounts();
}

function withdrawOrDeposit(accountNum) {
  const acc = findAccount(accountNum);
  if (!acc) return;

  const pinTry = prompt("Enter PIN:");
  if (pinTry !== acc.pin) {
    alert("Wrong PIN.");
    return;
  }

  const choice = prompt("1: Withdraw\n2: Deposit");
  if (choice === "1") {
    let amtStr = prompt("Amount to withdraw:");
    if (!/^\d+(\.\d+)?$/.test(amtStr)) {
      alert("Invalid amount.");
      return;
    }
    let amt = parseFloat(amtStr);
    if (amt > acc.balance) {
      alert("Cannot withdraw more than balance.");
      return;
    }
    acc.balance -= amt;
    acc.transactions.push({ type: "withdrawal", amount: amt });
  } else if (choice === "2") {
    let amtStr = prompt("Amount to deposit:");
    if (!/^\d+(\.\d+)?$/.test(amtStr)) {
      alert("Invalid amount.");
      return;
    }
    let amt = parseFloat(amtStr);
    acc.balance += amt;
    acc.transactions.push({ type: "deposit", amount: amt });
  }
  showAccounts();
}

function showTransactions(accountNum) {
  const acc = findAccount(accountNum);
  if (!acc) return;

  const pinTry = prompt("Enter PIN:");
  if (pinTry !== acc.pin) {
    alert("Wrong PIN.");
    return;
  }

  let message = "Transactions:\n";
  acc.transactions.forEach((tx, i) => {
    message += `${i+1}. ${tx.type} $${tx.amount.toFixed(2)}\n`;
  });
  alert(message);
}

function deleteAccount(accountNum) {
  accounts = accounts.filter(acc => acc.accountNum !== accountNum);
  showAccounts();
}
