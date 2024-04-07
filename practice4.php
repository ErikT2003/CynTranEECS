<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Practice4</title>
</head>
<body>
<h2>Multiplication Table Generator</h2>
<form method="post">
<label for="number">Enter a number:</label>
<input type="number" name="number" id="number">
<button type="submit">Generate Table</button>
</form>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
$number = $_POST["number"];
if (!empty($number)) {
echo "<h3>Multiplication Table up to $number</h3>";
echo "<table border='1'>";
echo "<tr><th>&times;</th>";
for ($i = 1; $i <= $number; $i++) {
echo "<th>$i</th>";
}
echo "</tr>";

for ($i = 1; $i <= $number; $i++) {
echo "<tr>";
echo "<th>$i</th>";
for ($j = 1; $j <= $number; $j++) {
echo "<td>" . ($i * $j) . "</td>";
}
echo "</tr>";
}
echo "</table>";
} else {
echo "<p>Please enter a number.</p>";
}
}
?>
</body>
</html>
