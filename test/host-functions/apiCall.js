// apiCall.js
// const fetch = require('node-fetch');

function makeAPICall(url) {
    console.log({ url }, "makeAPICall")
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve("node-fetch-mock-response")
        }, 3000);
    });
    // return fetch(url)
    //     .then(response => response.json())
    //     .catch(error => {
    //         console.error('Error fetching API:', error);
    //         throw error;
    //     });
}

module.exports = { makeAPICall };
