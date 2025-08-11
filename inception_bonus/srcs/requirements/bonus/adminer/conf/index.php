<?php
function adminer_object() {
    class AdminerAutoFill extends Adminer {
        function head() {
            parent::head();
            echo '<script type="text/javascript">
console.log("Adminer auto-fill script loaded via head");

function fillFields() {
    console.log("Attempting to fill login fields...");
    
    var server = document.querySelector("input[name=\"auth[server]\"]");
    var username = document.querySelector("input[name=\"auth[username]\"]");
    var password = document.querySelector("input[name=\"auth[password]\"]");
    var db = document.querySelector("input[name=\"auth[db]\"]");
    
    if (server) {
        server.value = "mariadb";
        console.log("✓ Server set to: mariadb");
    } else {
        console.log("✗ Server field not found");
    }
    
    if (username) {
        username.value = "sternero";
        console.log("✓ Username set to: sternero");
    } else {
        console.log("✗ Username field not found");
    }
    
    if (password) {
        password.value = "12345";
        console.log("✓ Password set");
    } else {
        console.log("✗ Password field not found");
    }
    
    if (db) {
        db.value = "wordpress_db";
        console.log("✓ Database set to: wordpress_db");
    } else {
        console.log("✗ Database field not found");
    }
}

// Try to fill fields when DOM is ready
if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function() {
        setTimeout(fillFields, 100);
        setTimeout(fillFields, 500);
        setTimeout(fillFields, 1000);
    });
} else {
    setTimeout(fillFields, 50);
    setTimeout(fillFields, 200);
    setTimeout(fillFields, 500);
}
</script>';
        }
    }
    
    return new AdminerAutoFill;
}

include '/var/www/html/adminer.php';
?>
