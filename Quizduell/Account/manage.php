<html>
    <head>
        <title>Quizduell - Manage Account</title>
        <link rel="stylesheet" href="style/login.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
        
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }

            if (isset($_GET['delete'])) {
                if($id > 3) $pdo->query("DELETE FROM login WHERE id =" . $id);
                if($id > 3) header("Location: ../index.php");
            }
        ?>
    </head>
    <body>
        <h1>Manage Account</h1>
        <hr>
        <br>
        <br>

        <?php
            foreach ($pdo->query("SELECT * FROM login") as $row){
                if($id == $row['id']){
                    echo "<p>Name: " . $row['name'] . "</p>";
                    echo "<p>E-Mail: " . $row['email'] . "</p>";
                    echo "<p>Total Points: " . $row['totalpoints'] . "</p>";
                    echo "<a href=\"manage.php?id=" . $id . "&delete=true\">Delete Account</a>";
                }
            }
        ?>

        <a href="../index.php?id=<?php echo $id ?>">Return to Menu</a>
    </body>
</html>