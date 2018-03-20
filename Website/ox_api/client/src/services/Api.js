//this is a connector to talk to our back end server.
import axios from 'axios'
//allows us to connect to our back end API.
export default () => {
    //Create an axios object, which points to our back end host 3000.
    return axios.create({
        baseURL: `http://localhost:3000/api/`
    })
}