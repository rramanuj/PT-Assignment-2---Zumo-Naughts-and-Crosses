// const passport = require('./passport')
// const {user} = require('./models')

// const JwtStrategy = require('passport-jwt').Strategy
// const ExtractJwt = require('passport-jwt').ExtractJwt


// const config = require('./config/config')

// passport.use (
//     new JwtStrategy({
//         jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(), //if someone makes  arequest with a bearber token it will use that
//         secretOrKey: config.authentication.jwtSecret
//     }, async function (jwtPayload, done) {
//         try {
//             const User = await user.findOne({
//                 where: {
//                     id: jwtPayload.id
//                 }
//             })
//             if (!user) {
//                 return done(new Error(), false)
//             }
//             return done(null, user)
            
//         }catch (err) {
//             return done(new Error(),false)
//         }
//     })
// )
// module.exports = null