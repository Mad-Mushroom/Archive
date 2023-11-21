/*
  CManager JavaScript Source code

  Copyright (c) 2023 MadMushroom / Benjamin Braun
*/

var contacts = []; // contacts Array (there is a better way to store this :)))) )

function saveContacts(){ // save Contacts function
  let contacts_sereliazed = JSON.stringify(contacts); // sereliaze array to JSON
  localStorage.setItem("contacts", contacts_sereliazed); // save JSON in local Storage
}

function loadContacts(){ // load Contacts function
  let contacts_desereliazed = JSON.parse(localStorage.getItem("contacts")); // desereliaze JSON Array
  contacts = contacts_desereliazed; // put desereliazed Data in Array
}

function ErrMsg(msg){ // function for Error (for example: "Contact already exists!")
  console.warn(msg); // print warning in console
  alert(msg); // display warning
}

function displayPopUpContainer(content){ // function to display something in a custom popup
  document.body.scrollTop = 0; // scroll to top (Safari)
  document.documentElement.scrollTop = 0; // scroll to top (Firefox, Chrome, Chromium, ...)
  var tempString = "<div class=\"popUpContainer\"><button id=\"closePopUpContainer\" onclick=\"removePopUpContainer()\">X</button>" + content + "</div>"; // set popup html
  document.getElementById("popUpContainerHolder").innerHTML = tempString; // write it to html
  var tempString = "<style media=\"screen\">#backgroundeffect{z-index: 8;width: 100%;height: 1000%;position: absolute;background-color: rgba(0, 0, 0, 0.5);}</style>" // set style of popup box
  document.getElementById("backgroundeffect").innerHTML = tempString; // write it to html
}

function removePopUpContainer(){ // functin to remove custom popup
  document.getElementById("popUpContainerHolder").innerHTML = ""; // set popup empty
  document.getElementById("backgroundeffect").innerHTML = ""; // set background effect to empty
}

function displayContactList(){ // function to display the list of contacts
  var tempString = ""; // string variable
  removePopUpContainer(); // remove any popups
  if(contacts.length <= 0){ tempString = "<p>No contacts yet.</p>" } // check if contacts is 0, if yes display info text
  for (let i = 0; i < contacts.length; i++){ // for all contacts in array
    let ti = i+1;  // no idea what this is...
    tempString += "<div id=\"contactListItem\"><p>" + "   " + contacts[i].LastName + " " + contacts[i].FirstName + "</p>" + "<button class=\"ContactOptionsDelete\" onclick=\"RemoveContact(" + i + ")\"><img src=\"img/icons/trash.png\" alt=\"Delete\"></button><button class=\"ContactOptions\" onclick=\"EditContact(" + i + ")\"><img src=\"img/icons/edit.png\" alt=\"Edit\"></button><button class=\"ContactOptions\" onclick=\"ShowDetails(" + i + ")\"><img src=\"img/icons/details.png\" alt=\"Details\"></button><br><br><br></div><br>"; // add one contact to list
  }
  document.getElementById("contactList").innerHTML = tempString; // display list
}

function ShowDetails(arrID){ // function to display details of contact
  var tempString = "<h2>Contact Details</h2><hr><p>First Name: " + contacts[arrID].FirstName + "</p><br><br><br><p>Last Name: " + contacts[arrID].LastName + "</p><br><br><br><p>Country: " + contacts[arrID].Country + "</p><br><br><br><p>City: " + contacts[arrID].City + "</p><br><br><br><p>Address: " + contacts[arrID].Address + "</p><br><br><br><p>Phone Number: " + contacts[arrID].PhoneNumber + "</p><br><br><br><p>Landline Number: " + contacts[arrID].LandlineNumber + "</p><br><br><br><p>E-Mail: " + contacts[arrID].Email + "</p>"; // details string
  displayPopUpContainer(tempString); // display details in popup
}

function FinalEdit(arrID){ // function when "Done" clicked by editing contact
  var firstname = document.getElementById("efirstname").value;
  var lastname = document.getElementById("elastname").value;
  var country = document.getElementById("ecountry").value;
  var city = document.getElementById("ecity").value;
  var address = document.getElementById("eaddress").value;
  var phonenumber = document.getElementById("ephonenumber").value;
  var landlinenumber = document.getElementById("elandlinenumber").value;
  var email = document.getElementById("eemail").value; // all details

  var newContact = {
    FirstName : firstname,
    LastName : lastname,
    Country : country,
    City : city,
    Address : address,
    PhoneNumber : phonenumber,
    LandlineNumber : landlinenumber,
    Email : email
  } // struct with details

  contacts[arrID] = newContact; // overwrite contact

  saveContacts(); // save contacts

  displayContactList(); // display contacts
}

function EditContact(arrID){ // function for editing contact
  var tempString = "<h2>Edit Contact</h2><hr><input placeholder=\"First Name\" id=\"efirstname\" value=\"" + contacts[arrID].FirstName + "\"><input placeholder=\"Last Name\" id=\"elastname\" value=\"" + contacts[arrID].LastName + "\"><br><br><input placeholder=\"Country\" id=\"ecountry\"  value=\"" + contacts[arrID].Country + "\"><input placeholder=\"City\" id=\"ecity\" value=\"" + contacts[arrID].City + "\"><input placeholder=\"Address\" id=\"eaddress\" value=\"" + contacts[arrID].Address + "\"><br><br><input placeholder=\"Phone Number\" id=\"ephonenumber\" value=\"" + contacts[arrID].PhoneNumber + "\"><input placeholder=\"Ladnline Number\" id=\"elandlinenumber\" value=\"" + contacts[arrID].LandlineNumber + "\"><input placeholder=\"E-Mail Address\" id=\"eemail\" value=\"" + contacts[arrID].Email + "\"><br><br><button id=\"EditDoneButton\" onclick=\"FinalEdit(" + arrID + ")\">Done</button><button id=\"EditCancelButton\" onclick=\"displayContactList()\">Cancel</button>"; // Edit html code in string
  displayPopUpContainer(tempString); // display string in popup
}

function AddContact(){ // function to add contact
  var firstname = document.getElementById("firstname").value;
  var lastname = document.getElementById("lastname").value;
  var country = document.getElementById("country").value;
  var city = document.getElementById("city").value;
  var address = document.getElementById("address").value;
  var phonenumber = document.getElementById("phonenumber").value;
  var landlinenumber = document.getElementById("landlinenumber").value;
  var email = document.getElementById("email").value; // details from inputs

  var newContact = {
    FirstName : firstname,
    LastName : lastname,
    Country : country,
    City : city,
    Address : address,
    PhoneNumber : phonenumber,
    LandlineNumber : landlinenumber,
    Email : email
  } // struct with all details

  let otherErr = 0; // error variable
  let hasBeenTaken = 0;// second error variable

  if(newContact.FirstName == "" || newContact.LastName == ""){ // check if name is empty
    ErrMsg("Not enough information!");
    otherErr = 1;
  }

  if(contacts.length >= 1 && otherErr == 0){ // check if name is present
    for (let i = 0; i < contacts.length; i++){ // for every contact in array
      if(contacts[i].FirstName == newContact.FirstName && contacts[i].LastName == newContact.LastName){ // check if name already exist
        hasBeenTaken = 1;
      }
    }
    if(hasBeenTaken == 1){ // check if error occured
      ErrMsg("Contact " + newContact.FirstName + " " + newContact.LastName + " already exists!");
      otherErr = 1;
    } else if(otherErr == 0) { // check if no error
      contacts.push(newContact); // add contact to array
      hasBeenTaken = 0;
    }
  } else if(otherErr == 0) { // check if no error
    contacts.push(newContact); // add contact to array
  }

  if(otherErr == 0 && hasBeenTaken == 0){ // check if no error
    saveContacts(); // save contacts
    document.getElementById("firstname").value = "";
    document.getElementById("lastname").value = "";
    document.getElementById("country").value = "";
    document.getElementById("city").value = "";
    document.getElementById("address").value = "";
    document.getElementById("phonenumber").value = "";
    document.getElementById("landlinenumber").value = "";
    document.getElementById("email").value = ""; // reset input-field text
    displayContactList(); // display contact list
  }
}

function ShowAddContactPopUp(){ // show popup to add contact
  var tempString = "<h2>Create new Contact</h2><hr><input placeholder=\"First Name\" id=\"firstname\"><input placeholder=\"Last Name\" id=\"lastname\"><br><br><input placeholder=\"Country\" id=\"country\"><input placeholder=\"City\" id=\"city\"><input placeholder=\"Address\" id=\"address\"><br><br><input placeholder=\"Phone Number\" id=\"phonenumber\"><input placeholder=\"Ladnline Number\" id=\"landlinenumber\"><input placeholder=\"E-Mail Address\" id=\"email\"><br><br><button id=\"AddContactButton\" onclick=\"AddContact()\">Add Contact</button><br><div id=\"addContactMsg\"></div><br><br>"; // input fields in string variable
  displayPopUpContainer(tempString); // display popup for adding contact
}

function RemoveContact(i){ // function to remove contact
  contacts.splice(i, 1); // remove contact from array
  saveContacts(); // save all contacts
  displayContactList(); // display contact list
}

function init(){ // initialize function
  loadContacts(); // load saved contacts
  displayContactList(); // display all contacts
}

init(); // at start call initialize function
