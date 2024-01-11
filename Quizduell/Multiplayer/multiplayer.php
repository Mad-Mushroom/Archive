<html>
    <head>
        <title>Quizduell - Multiplayer</title>
        <link rel="stylesheet" href="style/multiplayer.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            if($id == NULL){
                echo "<p style=\"font-size: 20px;\">Please log in to play Multiplayer!</p>";
                die("<br><a href=\"../index.php\" style=\"font-size: 20px;\">Return to Menu</a><br><a href=\"../Account/login.php\" style=\"font-size: 20px;\">Go to Login</a>");
            }

            if(isset($_POST['createRoom'])){
                $password = $_POST['password'];
                if($password == NULL) $password = 0;
                $pdo->query("INSERT INTO `multiplayer` (`id`, `roomcode`, `quiz`, `name`, `password`, `players`, `player1points`, `player2points`, `playersdone`) VALUES (NULL, '" . date("h") . date("i") . date("s") . "', 'Allgemeinwissen1',  '" . $_POST['name'] .  "', '" . $password .  "', '0', '0', '0', '0')");
            }

            if(isset($_GET['joinRoom'])){
                $players = 0;
                $roomCode = $_GET['joinRoom'];
                $quizPhp = "multigame.php";
                if($id <= 2) $quizPhp = "../Admin/a_multigame.php";
                foreach($pdo->query("SELECT * FROM multiplayer") as $row){
                    if($row['roomcode'] == $roomCode){
                        $players = $row['players'];
                    
                        if($players >= 2) die("Room Full!");
                    }
                }
                echo "2";

                if($players == 0) $plrNum = 1;
                if($players >= 1) $plrNum = 2;

                echo "3";

                $pdo->query("UPDATE multiplayer SET players = " . ++$players . " WHERE roomcode = $roomCode;");

                echo "4";

                header("Location: " . $quizPhp . "?roomcode=" . $roomCode . "&questionIndex=1&id=" . $id . "&playerNum=" . $plrNum);
            }

        ?>
    </head>
    <body>
        <h1>Multiplayer</h1>
        <hr>
        <div class="btn-group" id="mainDiv">
            <?php
                foreach($pdo->query("SELECT * FROM multiplayer") as $row){
                    $color = "green";
                    if($row['password'] == "0" && $row['players'] < 2){
                        echo "<button style=\"background-color: " . $color . ";\" onclick=\"window.location.href='" . "multiplayer.php" . "?joinRoom=" . $row['roomcode'] . "&id=" . $id . "'\">" . $row['name'] . "</button><br>";
                    }else if($row['players'] < 2){
                        $color = "red";
                        $roomCode = $row['roomcode'];
                        $password = $row['password'];
                        echo "<button style=\"background-color: " . $color . ";\" onclick=\"checkPassword()\">" . $row['name'] . "</button><br>";
                    }
                    if($row['players'] >= 2){
                        $color = "gray";
                        $roomCode = $row['roomcode'];
                        $password = $row['password'];
                        echo "<button style=\"background-color: " . $color . ";\" onclick=\"\">" . $row['name'] . "</button><br>";
                    }
                }
            ?>
            <br>
            <br>
            <br>

            <br>
            <br>
            <a href="multiplayer.php?id=<?php echo $id ?>">Refresh</a><br><br>

            <hr>
            <br>
            <button onclick="createRoomBtn()">Create Room</button><br><br>

            <script>
                function createRoomBtn(){
                    document.getElementById("mainDiv").innerHTML = "<form action=\"multiplayer.php?id=" + String("<?php Print($id); ?>") + "\" method=\"post\"><input type=\"text\" name=\"name\" placeholder=\"Name\"/><br /><br><input type=\"password\" name=\"password\" placeholder=\"Password (leave empty for no password)\"/><br /><br><input type=\"submit\" name=\"createRoom\" value=\"Create Room\" /></form>";
                }

                function checkPassword(){
                    document.getElementById("mainDiv").innerHTML = "<input id=\"passwordInput\" type=\"password\" placeholder=\"Password\"><br><button onclick=\"checkPass2()\">Join Room</button>";
                }

                function checkPass2(){
                    if(document.getElementById("passwordInput").value == String("<?php Print($password); ?>")){
                        window.location.href = "multiplayer.php?joinRoom=" + String("<?php Print($roomCode); ?>") + "&id=" + String("<?php Print($id); ?>");
                    }
                }
            </script>

            <a href="../index.php?id=<?php echo $id ?>">Return to Menu</a>
        </div>
    </body>
</html>