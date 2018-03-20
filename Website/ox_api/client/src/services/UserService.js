import API from '@/services/API'


export default {
  search(query) {
    return API().post('users', query);
}
};

