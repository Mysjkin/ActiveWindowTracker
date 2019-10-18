$(function(){
    function sendCurrentTab(){
        chrome.tabs.query({currentWindow: true, active: true}, function(tabs){
            var url = tabs[0].url;
            var match = url.match(/:\/\/(www[0-9]?\.)?(.[^/:]+)/i);
            if (match != null && match.length > 2 && typeof match[2] === 'string' && match[2].length > 0) {
                var $j = jQuery.noConflict();
                $j.ajax({
                    type: "POST",
                    url: "http://localhost:5000/add_entry",
                    contentType: "application/json",
                    crossDomain: false,
                    data: JSON.stringify({hostname: match[2]}),
                    dataType: 'json'
                });
            }
            else {
                console.log("No match");
            }
        });
    };
    $(document).ready(function() {
        $("#exportToDisk").click(sendCurrentTab);
    });
    chrome.windows.onFocusChanged.addListener(function(windowId) {
        if (windowId === -1) {
             console.log("Minimized");
        } else {
            chrome.windows.get(windowId, function(chromeWindow) {
                if (chromeWindow.state === "minimized") {
                    console.log("Minimized");
                } else {
                    console.log("NOT Minimized");
                }
            });
        }
    });
});