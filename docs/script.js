let accounts = [];

function createAccount() {
    let name = document.getElementById("nameInput").value.trim();
    let balance = document.getElementById("balanceInput").value.trim();
    let pin = document.getElementById("pinInput").value.trim();

    if (!/^[A-Za-z]+$/.test(name)) {
        alert("Name must contain only letters.");
        return;
    }
    if (isNaN(balance) || Number(balance) <= 0) {
        alert("Balance must be a positive number.");
        return;
    }
    if (!/^\d{4}$/.test(pin)) {
        alert("PIN must be exactly 4 digits.");
        return;
    }

    let accountNum = Math.floor(Math.random() * 9000) + 1000;
    let newAccount = {
        accountNum: accountNum,
        name: name,
        balance: parseFloat(balance),
        pin: pin,
        transactions: [{type: "Initial deposit", amount: parseFloat(balance)}]
    };

    accounts.push(newAccount);
    updateAccountList();
    clearInputs();
}

function updateAccountList() {
    let div = document.getElementById("accountList");
    div.innerHTML = "";
    accounts.forEach(acc => {
        let accDiv = document.createElement("div");
        accDiv.className = "account";
        accDiv.innerHTML = `#${acc.accountNum} - Name: ${acc.name}, Balance: $${acc.balance.toFixed(2)}, Transactions: ${acc.transactions.length}`;
        div.appendChild(accDiv);
    });
}

function clearInputs() {
    document.getElementById("nameInput").value = "";
    document.getElementById("balanceInput").value = "";
    document.getElementById("pinInput").value = "";
}

function editAccount() {
    let name = prompt("Enter account name to edit:");
    let account = accounts.find(acc => acc.name === name);

    if (!account) {
        alert("Account not found.");
        return;
    }

    let option = prompt(`Editing ${account.name}\n1: Change Name\n2: Change PIN\n3: Reset Balance\n0: Cancel`);
    if (option === "1") {
        let valid = false;
        while (!valid) {
            let newName = prompt("Enter new name (letters only):");
            if (/^[A-Za-z]+$/.test(newName)) {
                account.name = newName;
                valid = true;
                alert("Name updated.");
            } else {
                alert("Invalid name.");
            }
        }
    } else if (option === "2") {
        let valid = false;
        while (!valid) {
            let newPin = prompt("Enter new 4-digit PIN:");
            if (/^\d{4}$/.test(newPin)) {
                account.pin = newPin;
                valid = true;
                alert("PIN updated.");
            } else {
                alert("Invalid PIN.");
            }
        }
    } else if (option === "3") {
        account.balance = 0;
        account.transactions.push({type: "Reset", amount: 0});
        alert("Balance reset to $0 and transaction recorded.");
    } else if (option === "0") {
        alert("Cancelled.");
    } else {
        alert("Invalid option.");
    }
    updateAccountList();
}

function withdrawOrDeposit() {
    let name = prompt("Enter account name:");
    let account = accounts.find(acc => acc.name === name);
    if (!account) {
        alert("Account not found.");
        return;
    }

    let enteredPin = prompt("Enter PIN:");
    if (account.pin !== enteredPin) {
        alert("Incorrect PIN.");
        return;
    }

    let option = prompt("1: Withdraw\n2: Deposit");
    if (option === "1") {
        let amount = parseFloat(prompt("Enter withdrawal amount:"));
        if (isNaN(amount) || amount <= 0) {
            alert("Invalid amount.");
            return;
        }
        if (amount > account.balance) {
            alert("Cannot withdraw more than balance.");
            return;
        }
        account.balance -= amount;
        account.transactions.push({type: "Withdrawal", amount: amount});
        alert(`Withdrawn $${amount.toFixed(2)}. New balance: $${account.balance.toFixed(2)}`);
    } else if (option === "2") {
        let amount = parseFloat(prompt("Enter deposit amount:"));
        if (isNaN(amount) || amount <= 0) {
            alert("Invalid amount.");
            return;
        }
        account.balance += amount;
        account.transactions.push({type: "Deposit", amount: amount});
        alert(`Deposited $${amount.toFixed(2)}. New balance: $${account.balance.toFixed(2)}`);
    } else {
        alert("Invalid option.");
    }
    updateAccountList();
}

function deleteAccount() {
    let name = prompt("Enter account name to delete:");
    let index = accounts.findIndex(acc => acc.name === name);
    if (index === -1) {
        alert("Account not found.");
        return;
    }
    accounts.splice(index, 1);
    alert("Account deleted.");
    updateAccountList();
}

function showTransactions() {
    let name = prompt("Enter account name:");
    let account = accounts.find(acc => acc.name === name);
    if (!account) {
        alert("Account not found.");
        return;
    }
    let enteredPin = prompt("Enter PIN:");
    if (account.pin !== enteredPin) {
        alert("Incorrect PIN.");
        return;
    }
    let msg = `Transactions for ${account.name}:\n`;
    account.transactions.forEach((t, i) => {
        msg += `${i + 1}: ${t.type} - $${t.amount.toFixed(2)}\n`;
    });
    alert(msg);
}
