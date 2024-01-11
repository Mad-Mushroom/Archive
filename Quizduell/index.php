<html>
    <head>
        <title>Quizduell - Menu</title>
        <link rel="stylesheet" href="style/menu.css">
        <link rel = "icon" href="img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
        ?>
        <?php
            $quizzes[] = NULL;

            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }

            foreach ($pdo->query("SELECT * FROM quizzes") as $row) {
                array_push($quizzes, $row['name']);
            }

            function GetQuizzesDone(){
                global $qdone, $pdo, $id;
                $jsonString = '{}';
                foreach ($pdo->query("SELECT * FROM login") as $row) {
                    if($id == $row['id']) $jsonString = $row['completedquizzes'];
                }
                $qdone = json_decode($jsonString, true);
            }
        ?>
    </head>
    <body>
        <script>
            function NavigateTo(quizname){
                window.location.href = "Quiz/quiz.php?quizFile=" + quizname + "&questionIndex=1";
            }
        </script>

        <h1>Select Quiz:</h1>
        <hr>
        <br><br>
        <div class="btn-group">
            <?php
                foreach($quizzes as $quiz){
                    if($quiz != NULL){
                        $color = "blue";
                        $jsonString = '{}';
                        $quizPhp = "Quiz/quiz.php";
                        if($id <= 2 && $id >= 1) $quizPhp = "Admin/a_quiz.php";
                        foreach ($pdo->query("SELECT * FROM login") as $row) {
                            if($id == $row['id']) $jsonString = $row['completedquizzes'];
                        }
                        $qdone = json_decode($jsonString, true);
                        echo "<br>";
                        foreach($qdone as $doneQuiz => $val){
                            if($doneQuiz == $quiz) $color = "green";
                        }
                        if($quiz == "TestQuiz" && $id == 1 || $quiz == "TestQuiz" && $id == 2){
                            echo "<button style=\"background-color: " . $color . ";\" onclick=\"window.location.href='" . $quizPhp . "?quizFile=" . $quiz . "&questionIndex=1&id=" . $id . "'\">" . $quiz . "</button>";
                        }else if($quiz != "TestQuiz"){
                            echo "<button style=\"background-color: " . $color . ";\" onclick=\"window.location.href='" . $quizPhp . "?quizFile=" . $quiz . "&questionIndex=1&id=" . $id . "'\">" . $quiz . "</button>";
                        }
                    }
                }
            ?>

            <br>
            <br>
            <br>

            <hr>
            <br>
            <a href="Multiplayer/multiplayer.php?id=<?php echo $id ?>">Multiplayer</a><br><br>

            <hr>
            <br>
            <a href="Quiz/editor.php?newsession=true&id=<?php echo $id ?>">Open Editor</a>


            <br>
            <br>
            <hr>

            <?php
                $loggedIn = false;
                $name = NULL;
                $totalpoints = 0;
                foreach ($pdo->query("SELECT * FROM login") as $row) {
                   if($row['id'] == $id){
                    $name = $row['name'];
                    $totalpoints = $row['totalpoints'];
                    $loggedIn = true;
                   }
                }

                if($loggedIn == true){
                    echo "<br><p>Logged in as: " . $name . "</p><br><p>Total Points: " . $totalpoints . "</p><br><a href=\"Account/manage.php?id=" . $id . "\">Manage Account</a><br><a href=\"index.php\">Log out</a>";
                }

                if($loggedIn == false){
                    echo "<br><p>Not logged in.</p><a href=\"Account/login.php\">Login</a>";
                }
            ?><br>
        </div>
    </body>
</html>