<?php
echo "Content-Type: text/html\r\n\r\n";
echo "<html><body><h1>Hello from PHP CGI!</h1>";
$visit_count = isset($_SERVER['VISIT_COUNT']) ? $_SERVER['VISIT_COUNT'] : '0';
echo "<p>Visit count: $visit_count</p></body></html>";
?>