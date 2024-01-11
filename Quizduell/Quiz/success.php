<html>
    <head>
        <title>Quizduell</title>
        <link rel="stylesheet" href="style/success.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">

        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
            if (isset($_GET['points'])) {
                $points = $_GET['points'];
            }
            if($points <= 0){
                header("Location: ../index.php");
            }
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            $tp = 0;
            foreach ($pdo->query("SELECT * FROM login") as $row) {
                if($id == $row['id']) $tp = $row['totalpoints'];
            }
            $pdo->query("UPDATE login SET totalpoints =" . $points+$tp . " WHERE id = " . $id);
        ?>
    </head>
    <body>
        <div id="result">
            <p>total points: <?php echo $points; ?></p>
            <button onclick="startagain()">start again</button>
        </div>

        <script>
            function startagain(){
                window.location.href = "../index.php?id="  + String("<?php Print($id); ?>");
            }
        </script>
    </body>
</html>