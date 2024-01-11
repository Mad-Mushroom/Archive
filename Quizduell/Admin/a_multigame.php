<html>
    <head>
        <title>Quizduell - Multiplayer</title>
        <link rel="stylesheet" href="style/multigame.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
            $requestedQuiz=NULL;
            $id = 0;
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            if (isset($_GET['playerNum'])) {
                $playerNum = $_GET['playerNum'];
            }
            if($id == NULL || $id > 2){
                echo "<p style=\"font-size: 20px;\">Not an admin!</p>";
                die("<br><a href=\"../index.php\" style=\"font-size: 20px;\">Return to Menu</a>");
            }

            if(isset($_GET['roomcode'])){
                foreach($pdo->query("SELECT * FROM multiplayer") as $row){
                    if($row['roomcode'] == $_GET['roomcode']){
                        $found = true;
                        $roomcode = $row['roomcode'];
                        $requestedQuiz = $row['quiz'];
                    }
                }
                if($found != true) die("Could not find Room!");
            }

        ?>
        <?php
            $totalQuestions=0;
            $questionsArr[] = NULL;
            $ans1Arr[] = NULL;
            $ans2Arr[] = NULL;
            $ans3Arr[] = NULL;
            $ans4Arr[] = NULL;
            $ansNumArr[] = NULL;
            function LoadData(){
                global $questionsArr, $ans1Arr, $ans2Arr, $ans3Arr, $ans4Arr, $ansNumArr, $totalQuestions, $pdo, $requestedQuiz;
                foreach ($pdo->query("SELECT * FROM quizzes") as $row) {
                    if($requestedQuiz == $row['name']){
                        $questionsArr = json_decode($row['questions']);
                        $ans1Arr = json_decode($row['answer1']);
                        $ans2Arr = json_decode($row['answer2']);
                        $ans3Arr = json_decode($row['answer3']);
                        $ans4Arr = json_decode($row['answer4']);
                        $ansNumArr = json_decode($row['rightanswer']);
                        $totalQuestions = $row['totalquestions'];
                    }else if($row == NULL){
                        echo "Could not load Quiz!";
                    }
                }

            }
            LoadData();

            $questiontxt = "";
            $ans1txt = "";
            $ans2txt = "";
            $ans3txt = "";
            $ans4txt = "";

        ?>
    </head>
    <body>
    <p id="PointsText"><?php
            $points = 0;
            if (isset($_GET['points'])) {
                $points = $_GET['points'];
                if($playerNum == 1) $pdo->query("UPDATE multiplayer SET player1points = " . $points . " WHERE roomcode = $roomcode;");
                if($playerNum == 2) $pdo->query("UPDATE multiplayer SET player2points = " . $points . " WHERE roomcode = $roomcode;");
            }
            if (isset($_GET['questionIndex'])) {
                $questionIndex = $_GET['questionIndex'];
            }
            if($points == NULL){
                $points = 0;
            }
            if($questionIndex == NULL){
                header("Location: ../index.php");
            }

            $rightAnswer = $ansNumArr[$questionIndex];
            $questiontxt = $questionsArr[$questionIndex];
            $ans1txt = $ans1Arr[$questionIndex];
            $ans2txt = $ans2Arr[$questionIndex];
            $ans3txt = $ans3Arr[$questionIndex];
            $ans4txt = $ans4Arr[$questionIndex];

            if(--$questionIndex == $totalQuestions){
                header("Location: ../Multiplayer/multisuccess.php?points=$points&id=$id&roomcode=$roomcode&playerNum=$playerNum");
            }

            ++$questionIndex;

            echo $points;

        ?></p>
        <div id="question"><p><?php echo $questiontxt;?></p></div>
        <div id="answers">
            <button id="answer1" class="answerBtn" onclick="answer1Clicked()"><?php echo $ans1txt;?></button>
            <button id="answer2" class="answerBtn" onclick="answer2Clicked()"><?php echo $ans2txt;?></button>
            <button id="answer3" class="answerBtn" onclick="answer3Clicked()"><?php echo $ans3txt;?></button>
            <button id="answer4" class="answerBtn" onclick="answer4Clicked()"><?php echo $ans4txt;?></button>
        </div>

        <a href="../index.php?id=<?php echo $id ?>">Return to Menu</a>

        <div id="modmenu">
            <button onclick="window.location.href='../Multiplayer/multisuccess.php?points=<?php print($totalQuestions+$points) ?>&id=<?php print($id) ?>'">Instant Complete</button><br><br>
            <button onclick="window.location.href='a_multigame.php?points=<?php print(++$points); $points--; ?>&id=<?php print($id) ?>&questionIndex=<?php print(++$questionIndex); $questionIndex--; ?>&quizFile=<?php print($requestedQuiz) ?>&roomcode=<?php Print($roomcode); ?>&playerNum=<?php Print($playerNum); ?>'">Next Question (right answer)</button><br><br>
            <button onclick="window.location.href='a_multigame.php?points=<?php print($points) ?>&id=<?php print($id) ?>&questionIndex=<?php print(++$questionIndex); $questionIndex--; ?>&quizFile=<?php print($requestedQuiz) ?>&roomcode=<?php Print($roomcode); ?>&playerNum=<?php Print($playerNum); ?>'">Next Question (wrong answer)</button><br><br>
            <button onclick="window.location.href='a_multigame.php?points=<?php print(++$points); $points--; ?>&id=<?php print($id) ?>&questionIndex=<?php print($questionIndex); ?>&quizFile=<?php print($requestedQuiz) ?>&roomcode=<?php Print($roomcode); ?>&playerNum=<?php Print($playerNum); ?>'">Plus 1 Point</button>
            <button onclick="window.location.href='a_multigame.php?points=<?php print($points+10); $points -= 0; ?>&id=<?php print($id) ?>&questionIndex=<?php print($questionIndex); ?>&quizFile=<?php print($requestedQuiz) ?>&roomcode=<?php Print($roomcode); ?>&playerNum=<?php Print($playerNum); ?>'">Plus 10 Points</button>
            <button onclick="window.location.href='a_multigame.php?points=<?php print($points+100); $points -= 0; ?>&id=<?php print($id) ?>&questionIndex=<?php print($questionIndex); ?>&quizFile=<?php print($requestedQuiz) ?>&roomcode=<?php Print($roomcode); ?>&playerNum=<?php Print($playerNum); ?>'">Plus 100 Points</button><br><br>
        </div>

        <script>
            function answer1Clicked(){
                window.location.href = "a_multigame.php?ans1Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>") + "&roomcode=" + String("<?php Print($roomcode); ?>") + "&playerNum=" + String("<?php Print($playerNum); ?>");
            }
            function answer2Clicked(){
                window.location.href = "a_multigame.php?ans2Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>") + "&roomcode=" + String("<?php Print($roomcode); ?>") + "&playerNum=" + String("<?php Print($playerNum); ?>");;
            }
            function answer3Clicked(){
                window.location.href = "a_multigame.php?ans3Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>") + "&roomcode=" + String("<?php Print($roomcode); ?>") + "&playerNum=" + String("<?php Print($playerNum); ?>");;
            }
            function answer4Clicked(){
                window.location.href = "a_multigame.php?ans4Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>") + "&roomcode=" + String("<?php Print($roomcode); ?>") + "&playerNum=" + String("<?php Print($playerNum); ?>");;
            }
        </script>

        <?php
            function ansPress($clickedBtn){
                global $points, $ansNumArr, $questionIndex, $requestedQuiz, $id, $roomcode, $playerNum;
                if($ansNumArr[$questionIndex] == $clickedBtn){
                    header("Location: a_multigame.php?points=". ++$points. "&questionIndex=" . ++$questionIndex . "&quizFile=" . $requestedQuiz . "&id=" . $id . "&roomcode=" . $roomcode . "&playerNum=" . $playerNum);
                    exit;
                }
                if($ansNumArr[$questionIndex] != $clickedBtn){
                    header("Location: a_multigame.php?points=" . $points . "&questionIndex=" . ++$questionIndex . "&quizFile=" . $requestedQuiz . "&id=" . $id . "&roomcode=" . $roomcode . "&playerNum=" . $playerNum);    
                }
                exit;
            }

            if (isset($_GET['ans1Press'])) {
                ansPress(1);
            }
            if (isset($_GET['ans2Press'])) {
                ansPress(2);
            }
            if (isset($_GET['ans3Press'])) {
                ansPress(3);
            }
            if (isset($_GET['ans4Press'])) {
                ansPress(4);
            }
?>
    </body>
</html>