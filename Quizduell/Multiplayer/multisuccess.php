<html>
    <head>
        <title>Quizduell - Multiplayer</title>
        <link rel="stylesheet" href="style/success.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">

        <?php
            session_start();
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
            $wait = false;
            //$page = $_SERVER['PHP_SELF'];
            //$sec = "1";
            if (isset($_GET['points'])) {
                $points = $_GET['points'];
            }
            if(isset($_GET['roomcode'])) $roomcode = $_GET['roomcode'];
            if($points <= 0){
                header("Location: ../index.php");
            }
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            if(isset($_GET['delete'])){
                $pdo->query("DELETE FROM multiplayer WHERE roomcode = " . $roomcode);
                header("Location: ../index.php?id=$id");
            }
            if(isset($_GET['new'])) $_SESSION['plrdoneset'] = false;
            if(isset($_GET['playerNum'])){
                if(isset($_GET['roomcode'])){
                    foreach($pdo->query("SELECT * FROM multiplayer") as $row){
                        if($row['roomcode'] == $_GET['roomcode']){
                            if($_SESSION['plrdoneset'] == false) $pdo->query("UPDATE multiplayer SET playersdone = " . ++$row['playersdone'] . " WHERE roomcode = " . $_GET['roomcode']);
                            $_SESSION['plrdoneset'] = true;
                            if($_GET['playerNum'] == 1) $pointsOpp = $row['player2points'];
                            if($_GET['playerNum'] >= 2) $pointsOpp = $row['player1points'];
                            $_SESSION['pointsop'] = $pointsOpp;
                        }
                    }
                }
            }
            $pointsOpp = $_SESSION['pointsop'];
            $tp = 0;
            foreach ($pdo->query("SELECT * FROM login") as $row) {
                if($id == $row['id']) $tp = $row['totalpoints'];
            }
            $pdo->query("UPDATE login SET totalpoints =" . $points+$tp . " WHERE id = " . $id);
        ?>
    </head>
    <body>
        <div id="result">
            

            <?php
                if($wait == true){
                    echo "<p>please wait 'til all players are done :)</p><br>";
                    echo "<a href=\"multisuccess.php?points=$points&id=3&roomcode=$roomcode&playerNum=$playerNum\"></a>";
                }else{
                    echo "<p>total points: $points : </p>";
                    echo "<p> : total points of opponent: $pointsOpp</p>";
                    echo "<button onclick=\"startagain()\">return</button>";
                    session_destroy();
                }
            ?>
        </div>

        <script>
            function startagain(){
                window.location.href = "multisuccess.php?delete=true&id=" + String("<?php Print($id); ?>") + "&roomcode=" + String("<?php Print($roomcode); ?>");
            }
        </script>
    </body>
</html>