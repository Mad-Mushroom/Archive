<html>
    <head>
        <title>Quizduell</title>
        <link rel="stylesheet" href="style/quiz.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        <?php
            $totalQuestions=0;
            $requestedQuiz=NULL;
            
            if (isset($_GET['quizFile'])) {
                $requestedQuiz = $_GET['quizFile'];
            }
            $questionsArr[] = NULL;
            $ans1Arr[] = NULL;
            $ans2Arr[] = NULL;
            $ans3Arr[] = NULL;
            $ans4Arr[] = NULL;
            $ansNumArr[] = NULL;
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');
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
            $id = NULL;
            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            if($id == NULL){
                echo "<p style=\"font-size: 20px;\">Please log in to play Quiz!</p>";
                echo "<br><a href=\"../index.php\" style=\"font-size: 20px;\">Return to Menu</a><br><a href=\"../Account/login.php\" style=\"font-size: 20px;\">Go to Login</a>";
            }
            if (isset($_GET['points'])) {
                $points = $_GET['points'];
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

            function MarkQuizDone(){
                global $id, $requestedQuiz, $pdo;
                $jsonString = '{}';
                foreach ($pdo->query("SELECT * FROM login") as $row) {
                    if($id == $row['id']) $jsonString = $row['completedquizzes'];
                }
                $qdone = json_decode($jsonString, true);
                $qdone[$requestedQuiz] = true;
                $jsonString = json_encode($qdone);
                $pdo->query("UPDATE login SET completedquizzes = '" . $jsonString . "' WHERE id = " . $id);
            }

            MarkQuizDone();

            $rightAnswer = $ansNumArr[$questionIndex];
            $questiontxt = $questionsArr[$questionIndex];
            $ans1txt = $ans1Arr[$questionIndex];
            $ans2txt = $ans2Arr[$questionIndex];
            $ans3txt = $ans3Arr[$questionIndex];
            $ans4txt = $ans4Arr[$questionIndex];

            if(--$questionIndex == $totalQuestions){
                header("Location: success.php?points=$points&id=$id");
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

        <script>
            function answer1Clicked(){
                window.location.href = "quiz.php?ans1Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>");
            }
            function answer2Clicked(){
                window.location.href = "quiz.php?ans2Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>");
            }
            function answer3Clicked(){
                window.location.href = "quiz.php?ans3Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>");
            }
            function answer4Clicked(){
                window.location.href = "quiz.php?ans4Press=true&points=" + <?php Print($points); ?> + "&questionIndex=" + <?php Print($questionIndex); ?> + "&quizFile=" + String("<?php Print($requestedQuiz); ?>") + "&id=" + String("<?php Print($id); ?>");
            }
        </script>

        <?php
            function ansPress($clickedBtn){
                global $points, $ansNumArr, $questionIndex, $requestedQuiz, $id;
                if($ansNumArr[$questionIndex] == $clickedBtn){
                    header("Location: quiz.php?points=". ++$points. "&questionIndex=" . ++$questionIndex . "&quizFile=" . $requestedQuiz . "&id=" . $id);
                    exit;
                }
                if($ansNumArr[$questionIndex] != $clickedBtn){
                    header("Location: quiz.php?points=" . $points . "&questionIndex=" . ++$questionIndex . "&quizFile=" . $requestedQuiz . "&id=" . $id);    
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
