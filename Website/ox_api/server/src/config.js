module.exports = {
    authentication: {
        jwtSecret: process.env.JWT_SECRET || 'secret' //this secret is only stored on the server
        //to validate whether the token is real or not. Because technically anyone can go to jwt.io and create their own token
        //and send it to my server, but if they dont know the secret then JWT won't accept it.
    }
}