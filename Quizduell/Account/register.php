<html>
    <head>
        <title>Quizduell - Register</title>
        <link rel="stylesheet" href="style/login.css">
        <link rel = "icon" href="../img/icon.png" type = "image/x-icon">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
        
        <?php
            $pdo = new PDO('mysql:host=localhost;dbname=quizduell_login;charset=utf8', 'root', '');

            $edkey = "FU625x3BYr2HIgTNzfkz76BdAGeoTOVg";

            function safeDecrypt(string $encrypted, string $key): string{
                $ciphering = "AES-128-CTR";
                $decryption_iv = '1234567891011121';
                $options = 0;
                $decryption_key = $key;

                $decryption=openssl_decrypt ($encrypted, $ciphering, 
                $decryption_key, $options, $decryption_iv);

                return $decryption;
            }
            function safeEncrypt(string $message, string $key): string{
                $ciphering = "AES-128-CTR";
 
                $iv_length = openssl_cipher_iv_length($ciphering);
                $options = 0;

                $encryption_iv = '1234567891011121';

                $encryption_key = $key;

                $encryption = openssl_encrypt($message, $ciphering,
                $encryption_key, $options, $encryption_iv);

                return $encryption;
            }
        ?>
    </head>
    <body>
        <h1>Register</h1>
        <hr>
        <br>
        <br>
        <form action="register.php" method="post">
            <input type="text" name="name" placeholder="Name"/><br />
            <br>
            <input type="email" name="email" placeholder="E-Mail"/><br />
            <br>
            <input type="password" name="password" placeholder="Password"/><br />
            <br>
            <input type="submit" name="submit" value="Register" />
        </form>

        <?php
            $id = 0;
            foreach ($pdo->query("SELECT * FROM login") as $row) {
                $id = ++$row['id'];
            }
            $name = $_POST['name'];
            $email = $_POST['email'];
            $password = $_POST['password'];
            if($name != NULL && $email != NULL && $password != NULL){
                $pdo->query("INSERT INTO `login` (`id`, `name`, `email`, `password`, `totalpoints`, `completedquizzes`) VALUES ('" . $id . "', '" . $name . "', '" . $email . "', '" . safeEncrypt($password, $edkey) . "', '0', '{\"allgemeinwissen1\": \"false\"}') ");
                header("Location: ../index.php?id=" . $id);
            }
        ?>
    </body>
</html>
