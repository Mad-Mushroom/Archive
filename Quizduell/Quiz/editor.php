<html>
    <head>
        <title>Quizduell - Editor</title>
        <link rel="stylesheet" href="style/editor.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        <?php
            session_start();

            $quizName = NULL;
            $questionsArr[] = NULL;
            $ans1Arr[] = NULL;
            $ans2Arr[] = NULL;
            $ans3Arr[] = NULL;
            $ans4Arr[] = NULL;
            $ansNumArr[] = NULL;
            $totalQuestions = 0;
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');

            if (isset($_GET['id'])) {
                $id = $_GET['id'];
            }
            if (isset($_POST['id'])) {
                $id = $_POST['id'];
            }

            if (isset($_GET['newsession'])) {
                session_destroy();
            }

            if($_SESSION['totalQuestions'] != NULL){
                $totalQuestions = $_SESSION['totalQuestions'];
            }
            if($_SESSION['questionsArr'] != NULL){
                $questionsArr = $_SESSION['questionsArr'];
            }
            if($_SESSION['ans1Arr'] != NULL){
                $ans1Arr = $_SESSION['ans1Arr'];
            }
            if($_SESSION['ans2Arr'] != NULL){
                $ans2Arr = $_SESSION['ans2Arr'];
            }
            if($_SESSION['ans3Arr'] != NULL){
                $ans3Arr = $_SESSION['ans3Arr'];
            }
            if($_SESSION['ans4Arr'] != NULL){
                $ans4Arr = $_SESSION['ans4Arr'];
            }
            if($_SESSION['ansNumArr'] != NULL){
                $ansNumArr = $_SESSION['ansNumArr'];
            }

            
        ?>
    </head>
    <body>
        <form action="editor.php" method="post">
            <input name="id" value="<?php echo $id ?>" style="margin-top: -100px;">
            <input name="questionsArr" value="<?php echo $questionsArr ?>" style="margin-top: -100px;">
            <input name="ans1Arr" value="<?php echo $ans1Arr ?>" style="margin-top: -100px;"><input name="ans2Arr" value="<?php echo $ans2Arr ?>" style="margin-top: -100px;"><input name="ans3Arr" value="<?php echo $ans3Arr ?>" style="margin-top: -100px;"><input name="ans4Arr" value="<?php echo $ans4Arr ?>" style="margin-top: -100px;">
            <input name="ansNumArr" value="<?php echo $ansNumArr ?>" style="margin-top: -100px;">

            <input name="qname" placeholder="QuizName" value="<?php echo isset($_POST['qname']) ? $_POST['qname'] : '' ?>">
            <div id="question"><input name="question" placeholder="Question"></div>
            <input id="ranswer" name="rightAnswer" placeholder="Right Answer">
            <div id="answers">
                <input id="answer1" class="answerBtn" name="answer1" placeholder="Answer1">
                <input id="answer2" class="answerBtn" name="answer2" placeholder="Answer2">
                <input id="answer3" class="answerBtn" name="answer3" placeholder="Answer3">
                <input id="answer4" class="answerBtn" name="answer4" placeholder="Answer4">
                <br><br>
                <input type="submit" name="submit" value="Next Question"/>
                <input type="submit" name="finish" value="Upload Quiz"/>
            </div>
        </form>

        <br><br><br><br>
        <a href="../index.php?id=<?php echo $id ?>">Return to Menu</a>

        <?php
            $question = $_POST['question'];
            $rightAnswer = $_POST['rightAnswer'];
            $answer1 = $_POST['answer1'];
            $answer2 = $_POST['answer2'];
            $answer3 = $_POST['answer3'];
            $answer4 = $_POST['answer4'];
            $qname = $_POST['qname'];

            $id= $_POST['id'];

            if (isset($_POST['finish'])) {
                $pdo->query("INSERT INTO `quizzes` (`name`, `totalquestions`, `questions`, `answer1`, `answer2`, `answer3`, `answer4`, `rightanswer`) VALUES ('" . $qname . "', '" . $totalQuestions . "', '" . json_encode($questionsArr) . "', '" . json_encode($ans1Arr) . "', '" . json_encode($ans2Arr) . "', '" . json_encode($ans3Arr) . "', '" . json_encode($ans4Arr) . "', '" . json_encode($ansNumArr) . "')");
                header("Location: ../index.php?id=" . $id);
            }

            if($question != NULL && $rightAnswer != NULL && $answer1 != NULL && $answer2 != NULL && $answer3 != NULL && $answer4 != NULL && $qname != NULL){
                $quizName = $qname;
                array_push($questionsArr, $question);
                array_push($ans1Arr, $answer1);
                array_push($ans2Arr, $answer2);
                array_push($ans3Arr, $answer3);
                array_push($ans4Arr, $answer4);
                array_push($ansNumArr, $rightAnswer);

                if(isset($_POST['submit'])){
                    $totalQuestions++;
                }

                $_SESSION['totalQuestions'] = $totalQuestions;
                $_SESSION['questionsArr'] = $questionsArr;
                $_SESSION['ans1Arr'] = $ans1Arr;
                $_SESSION['ans2Arr'] = $ans2Arr;
                $_SESSION['ans3Arr'] = $ans3Arr;
                $_SESSION['ans4Arr'] = $ans4Arr;
                $_SESSION['ansNumArr'] = $ansNumArr;
            }
        ?>
    </body>
</html>