
var helloWorldDll = null;

function initExtension(extensionDir) {
    try {
        helloWorldDll = new ExternalObject("lib:" + "HelloWorld.dll");
    } catch (e) {
        alert("exception: " + e);
    }
}

initExtension();
function showAlertMessage(index) {
    // Acquire message corresponding to number (index)
    var message = helloWorldDll.extGetAlertMessage(index);
    alert(message);
}
function showAlertMessageDefault() {
    // Acquire default message
    var message = helloWorldDll.extGetAlertMessageDefault();
    alert(message);
}

showAlertMessage(1);